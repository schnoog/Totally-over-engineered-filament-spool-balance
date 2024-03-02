#pragma once

#include <homewifi.h>
#include <humidity.h>
//const char *topic = "3d/filamentbalance";

int SubCNT = 0;
int SendEach = 3;

void PublishWeights(){
    String topicWithWeight;
    Serial.print("Publishing (1/2/3/4): ");
    for (int i = 0; i < NUM_LOAD_CELLS; ++i) {

        // Convert the integer value to a string
        char weightAsString[10]; // Adjust the size as needed
        snprintf(weightAsString, sizeof(weightAsString), "%d", WeightInG[i]);
        Serial.print(WeightInG[i]);
        Serial.print(" ");
        // Construct the topic with "/weight/" + current index i
        char topicWithWeight[50]; // Adjust the size as needed
        snprintf(topicWithWeight, sizeof(topicWithWeight), "%s/weight/%d", topic, i + 1);
        
        // Concatenate the weight string with the topic
        char message[60]; // Adjust the size as needed
        snprintf(message, sizeof(message), "%s: %s", topicWithWeight, weightAsString);
        
        // Publish using the constructed message
        SubCNT++;
        if(SubCNT == SendEach){
            SubCNT = 0;
            client.publish(topicWithWeight, message);
        }
        

        // Construct the topic with "/emptyspool/" + current index i
        char topicWithEmptySpool[50]; // Adjust the size as needed
        snprintf(topicWithEmptySpool, sizeof(topicWithEmptySpool), "%s/emptyspool/%d", topic, i + 1);

        // Convert the integer value to a string
        char emptySpoolAsString[10]; // Adjust the size as needed
        snprintf(emptySpoolAsString, sizeof(emptySpoolAsString), "%d", EmptySpool[i]);

        // Concatenate the empty spool string with the topic
        char messageEmptySpool[60]; // Adjust the size as needed
        snprintf(messageEmptySpool, sizeof(messageEmptySpool), "%s: %s", topicWithEmptySpool, emptySpoolAsString);

        // Publish using the constructed message
        SubCNT++;
        if(SubCNT == SendEach){
            SubCNT = 0;
            client.publish(topicWithEmptySpool, messageEmptySpool);
        }


    }






        char tempStr[10]; // Allocate space for the temperature string
        char humStr[10];  // Allocate space for the humidity string
        dtostrf(Temperature, 4, 1, tempStr); // Convert temperature float to string
        dtostrf(Humidity, 4, 1, humStr);     // Convert humidity float to string
        int topicLength = strlen(topic);
        int appendLength = strlen("/temperature");
        char *newTopicT = new char[topicLength + appendLength + 1];
        strcpy(newTopicT, topic);
        strcat(newTopicT, "/temperature");
        appendLength = strlen("/humidity");
        char *newTopicH = new char[topicLength + appendLength + 1];
        strcpy(newTopicH, topic);
        strcat(newTopicH, "/humidity");        
        client.publish(newTopicT,tempStr);
        client.publish(newTopicH,humStr);












    Serial.println("");
}

String commandCMD;
String parameterCMD;
float floatValueCMD;
int intValueCMD;


void workOnCommand(){
    
}


void callback(char *topic, byte *payload, unsigned int length) {
    Serial.print("Message arrived in topic: ");
    Serial.println(topic);
    Serial.print("Message:");

    // Parse payload into a string
    String message;
    for (int i = 0; i < length; i++) {
        message += (char)payload[i];
    }
    Serial.println(message);

    // Split the message into command and parameter (if any)
//    String command;
//    String parameter;
    int spaceIndex = message.indexOf(' ');
    if (spaceIndex != -1) { // If there's a space, then there's a parameter
        commandCMD = message.substring(0, spaceIndex);
        parameterCMD = message.substring(spaceIndex + 1);
    } else { // If no space, the whole message is the command
        commandCMD = message;
    }

    // Print parsed command and parameter
    Serial.print("Command: ");
    Serial.println(commandCMD);
    Serial.print("Parameter: ");
    Serial.println(parameterCMD);

    // Check if parameter is numeric and save it as int or float
    bool isNumeric = true;
    for (int i = 0; i < parameterCMD.length(); i++) {
        if (!isdigit(parameterCMD.charAt(i)) && parameterCMD.charAt(i) != '.') {
            isNumeric = false;
            break;
        }
    }

    if (isNumeric) {
        if (parameterCMD.indexOf('.') != -1) {
            // Parameter is a float
            floatValueCMD = parameterCMD.toFloat();
            Serial.print("Parameter (float): ");
            Serial.println(floatValueCMD);
            // Save floatValueCMD for further use
        } else {
            // Parameter is an integer
            intValueCMD = parameterCMD.toInt();
            Serial.print("Parameter (int): ");
            Serial.println(intValueCMD);
            // Save intValueCMD for further use
        }
    } else {
        Serial.println("Parameter is not numeric.");
    }
    Serial.println("-----------------------");
}
