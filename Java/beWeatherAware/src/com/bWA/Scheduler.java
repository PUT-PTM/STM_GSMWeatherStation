package com.bWA;

import java.io.*;
import java.util.Timer;
import java.util.Date;
import java.util.TimerTask;

/**
 *  Scheduler - klasa zarzadzajaca calym projektem.
 *  Z racji tego, ze dane na serwerze pogodowym sa aktualizowane raz na 20 min, nie ma potrzeby co chwile odpytywac
 *  serwer o nowe warunki, dlatego tez zastosowalem Timer, ktory raz na 20 min wykonuje cala niezbedna sekwencje:
 *      1 - pobiera warunki pogodowe (calego JSONa) z serwera,
 *      2 - wysyla do mikrokontrolera flage 's' informujaca urzadzenie, aby zaczelo wysylac zmierzone przez siebie warunki,
 *      3 - zaczyna odbierac dane z STM32,
 *      4 - zapisuje JSONa do pliku,
 *      5 - zapisuje warunki panujace na zewnatrz budunku (z serwera) i wewnatrz budynku (z czujnikow w STM32) do pliku,
 *      6 - wysyla pobrane przez siebie warunki pogodowe do STM32, aby mikrokontroler mogl je dalej przekazac przez GSM,
 *      7 - czeka 20 min.
 */

public class Scheduler {

    private Timer timer;
    private WeatherConditions weatherConditions;
    private UART uart;

    Scheduler() throws IOException {
        this.timer = new Timer();
        this.weatherConditions = new WeatherConditions();

        try {
            uart = new UART(weatherConditions);
            uart.connect();
        } catch (Exception e) {
            e.printStackTrace();
        }
        
        startScheduler();
    }

    private void startScheduler() {
        Thread.UncaughtExceptionHandler uncaught = (thread, ex) -> System.out.println("Uncaught exception " + ex);

        Thread thread = new Thread(() -> timer.scheduleAtFixedRate(new TimerTask() {
            @Override
            public void run() {
                try {
                    weatherConditions.getConditionsFromWeb();
                    uart.sendToStm("s");
                    // czekamy na przeslanie wszystkich danych z STMa, zebysmy mogli je zapisac
                    Thread.sleep(500);
                    weatherConditions.saveJsonToFile();
                    weatherConditions.saveConditionsToFile();
                    uart.sendToStm(weatherConditions.getConditionsForStm());
                } catch (IOException e) {
                    e.printStackTrace();
                } catch (Exception e) {
                    e.printStackTrace();
                }
            }
        }, new Date(), 1000 * 10));
        // 1000 * 60 * 20 - 20 min
        thread.setUncaughtExceptionHandler(uncaught);
        thread.start();
    }
}