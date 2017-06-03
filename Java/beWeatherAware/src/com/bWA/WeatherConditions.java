package com.bWA;

import java.io.*;
import java.net.URL;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.nio.charset.Charset;
import org.json.JSONException;
import org.json.JSONObject;

/**
 *  WeatherConditions - klasa odpowiedzialna za:
 *      - pobieranie warunkow pogodowych z serwera                  -   getConditionsFromWeb();
 *      - pobieranie warunkow pogodowych z mikrokontrolera STM32    -   getConditionsFromStm();
 *      - zapis pobranych warunkow pogodowych do pliku              -   saveConditionsToFile();
 *      - zapis odpowiedzi serwera w postaci JSON do pliku          -   saveJsonToFile();
 *      - przygotowanie danych do wyslania do mikrokontrolera       -   getConditionsForStm();
 */

public class WeatherConditions {

    private static final String URL = "http://api.wunderground.com/api/87ae69beda4a103a/forecast/geolookup/conditions/q/pws:IPOZNA72.json";
    private static final String PATH_OF_FULL_RESPONSE = "D:\\beWeatherAware\\logs\\full-json-response.txt";
    private static final String PATH_OF_CONDITIONS_LOG = "D:\\beWeatherAware\\logs\\weather-conditions-log.txt";

    private String [] conditionsFromWeb;
    private String [] conditionsFromStm;
    private String jsonText;

    WeatherConditions() throws IOException, JSONException  {
        /*
         *  0 - temperatura
         *  1 - cisnienie
         *  2 - wilgotnosc
         */
        conditionsFromWeb = new String[3];
        conditionsFromStm = new String[3];
    }

    public void getConditionsFromWeb() throws IOException, JSONException {
        JSONObject jsonObject = readJsonFromUrl();

        conditionsFromWeb[0] = String.valueOf((int)(jsonObject.getJSONObject("current_observation").getDouble("temp_c")));
        conditionsFromWeb[1] = jsonObject.getJSONObject("current_observation").getString("pressure_mb");
        conditionsFromWeb[2] = jsonObject.getJSONObject("current_observation").getString("relative_humidity").substring(0,2);
    }

    public void getConditionsFromStm(String conditionsStm) {
        /*
            Co orzymujemy: 12100546.
            Gdzie 12 to temp, 1005 to cisnienie, 46 to wilgotnosc.
         */

        if (conditionsStm.charAt(0) == '0') {
            conditionsFromStm[0] = conditionsStm.substring(1,2);
        } else {
            conditionsFromStm[0] = conditionsStm.substring(0,2);
        }

        if (conditionsStm.charAt(2) == '0') {
            conditionsFromStm[1] = conditionsStm.substring(3,6);
        } else {
            conditionsFromStm[1] = conditionsStm.substring(2,6);
        }

        conditionsFromStm[2] = conditionsStm.substring(6,8);

        System.out.println("From STM -> " + conditionsStm +" where temp: " + conditionsFromStm[0] + " press: " + conditionsFromStm[1] + " hum: " + conditionsFromStm[2]); /**********************************************************/
    }

    public String getConditionsForStm() {
        String conditionsForStm = "";

        if (Integer.parseInt(conditionsFromWeb[0]) < 10) {
            conditionsForStm += "0";
            conditionsForStm += conditionsFromWeb[0];
        } else {
            conditionsForStm += conditionsFromWeb[0];
        }

        if (Integer.parseInt(conditionsFromWeb[1]) < 1000) {
            conditionsForStm += "0";
            conditionsForStm += conditionsFromWeb[1];
        } else {
            conditionsForStm += conditionsFromWeb[1];
        }

        conditionsForStm += conditionsFromWeb[2];

        System.out.println("For  STM -> " + conditionsForStm + " where temp: " + conditionsFromWeb[0] + " press: " + conditionsFromWeb[1] + " hum: " + conditionsFromWeb[2]); /**********************************************************/

        return conditionsForStm;
    }

    public void saveJsonToFile() throws IOException {
        File file = new File(PATH_OF_FULL_RESPONSE);

        if (!file.exists()) {
            file.createNewFile();
        }

        FileWriter fileWriter = new FileWriter(file);
        fileWriter.write(jsonText);
        fileWriter.close();
    }

    public void saveConditionsToFile() throws IOException{
        File file = new File(PATH_OF_CONDITIONS_LOG);

        if (!file.exists()) {
            file.createNewFile();
        }

        SimpleDateFormat format = new SimpleDateFormat ("E',' dd/MM/yyyy  HH:mm:ss");

        FileWriter fileWriter = new FileWriter(file, true);
        fileWriter.write("##########################\n");
        fileWriter.write(format.format(new Date()) + "\n");
        fileWriter.write("##########################\n");
        fileWriter.write("Outside conditions: \n");
        fileWriter.write("\ttemperature: " + conditionsFromWeb[0] + "C\n");
        fileWriter.write("\tpressure: " + conditionsFromWeb[1] + "hPa\n");
        fileWriter.write("\thumidity: " + conditionsFromWeb[2] + "%\n");
        fileWriter.write("Inside conditions: \n");
        fileWriter.write("\ttemperature: " + conditionsFromStm[0] + "C\n");
        fileWriter.write("\tpressure: " + conditionsFromStm[1] + "hPa\n");
        fileWriter.write("\thumidity: " + conditionsFromStm[2] + "%\n");
        fileWriter.close();
    }

    private String readAll(Reader reader) throws IOException {
        StringBuilder stringBuilder = new StringBuilder();
        int cp;

        while ((cp = reader.read()) != -1) {
            stringBuilder.append((char) cp);
        }

        return stringBuilder.toString();
    }

    private JSONObject readJsonFromUrl() throws IOException, JSONException {
        InputStream inputStream = new URL(URL).openStream();

        try {
            BufferedReader reader = new BufferedReader(new InputStreamReader(inputStream, Charset.forName("UTF-8")));
            jsonText = "";
            jsonText = readAll(reader);
            JSONObject jsonObject = new JSONObject(jsonText);
            return jsonObject;
        } finally {
            inputStream.close();
        }
    }
}