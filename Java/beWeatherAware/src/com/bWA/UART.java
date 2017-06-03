package com.bWA;

import gnu.io.CommPort;
import gnu.io.CommPortIdentifier;
import gnu.io.SerialPort;
import gnu.io.SerialPortEvent;
import gnu.io.SerialPortEventListener;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

/**
 *  UART - klasa odpowiedzialna za wysylanie i otrzymywanie danych z interfejsu UART RS232.
 */

public class UART {

    private static final String PORT_NAME = "COM4";
    private static final int BAUD = 115200;

    private CommPortIdentifier commPortIdentifier;
    private CommPort commPort;
    private SerialPort serialPort;
    private InputStream inputStream;
    private OutputStream outputStream;
    private WeatherConditions weatherConditions;

    public UART(WeatherConditions weatherConditions) {
        this.weatherConditions = weatherConditions;
    }

    public void sendToStm(String s) {
        (new Thread(new SerialWriter(outputStream, s))).start();
    }

    public void connect() throws Exception {
        commPortIdentifier = CommPortIdentifier.getPortIdentifier(PORT_NAME);

        if (commPortIdentifier.isCurrentlyOwned()) {
            System.out.println("Error: Port is currently in use.");
        } else {
            // wskazuje kto posiada port oraz okresla connection timeout
            commPort = commPortIdentifier.open(this.getClass().getName(), 2000);

            if (commPort instanceof SerialPort) {
                serialPort = (SerialPort) commPort;

                // ustawia parametry polaczenia
                serialPort.setSerialPortParams(BAUD, SerialPort.DATABITS_8, SerialPort.STOPBITS_1, SerialPort.PARITY_NONE);

                inputStream = serialPort.getInputStream();
                outputStream = serialPort.getOutputStream();

                serialPort.addEventListener(new SerialReader(inputStream));
                serialPort.notifyOnDataAvailable(true);
            } else {
                System.out.println("Error: Only serial ports are handled by this example.");
            }
        }
    }

    private class SerialWriter implements Runnable {

        private OutputStream out;
        private byte[] bytes;

        public SerialWriter(OutputStream out, String s) {
            this.out = out;
            bytes = s.getBytes();
        }

        public void run() {
            try {
                for (int i = 0; i < bytes.length; i++) {
                    this.out.write(bytes[i]);
                    // opoznienie dodalem, zeby STM mogl przetworzyc otrzymane dane i podjac odpowiednie kroki
                    Thread.sleep(10);
                }
            } catch (IOException e) {
                e.printStackTrace();
                System.exit(-1);
            } catch (Exception e) {
                e.printStackTrace();
                System.exit(-1);
            }
        }
    }

    private class SerialReader implements SerialPortEventListener {

        private InputStream in;
        private byte[] buffer;
        private String conditionsFromStm;

        public SerialReader(InputStream in) {
            this.in = in;
            buffer = new byte[1024];
            conditionsFromStm = "";
        }

        public void serialEvent(SerialPortEvent arg0) {
            int data;

            try {
                int length = 0;

                while ((data = in.read()) > -1) {
                    if (data == '\n') {
                        break;
                    }
                    buffer[length++] = (byte) data;
                }
                String s = new String(buffer, 0, length);
                conditionsFromStm += s;

                // 2 znaki na temp + 4 na cisnienie + 2 na wilgotnosc = 8
                if (conditionsFromStm.length() >= 8) {
                    weatherConditions.getConditionsFromStm(conditionsFromStm);
                    conditionsFromStm = "";
                }
            } catch (IOException e) {
                e.printStackTrace();
                System.exit(-1);
            }
        }
    }
}
