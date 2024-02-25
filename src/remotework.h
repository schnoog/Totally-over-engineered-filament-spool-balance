#pragma once

#include <homewifi.h>
//const char *topic = "3d/filamentbalance";
void PublishWeights(){
    String topicWithWeight;
    for (int i = 0; i < NUM_LOAD_CELLS; ++i) {

        // Convert the integer value to a string
        char weightAsString[10]; // Adjust the size as needed
        snprintf(weightAsString, sizeof(weightAsString), "%d", WeightInG[i]);
        
        // Construct the topic with "/weight/" + current index i
        char topicWithWeight[50]; // Adjust the size as needed
        snprintf(topicWithWeight, sizeof(topicWithWeight), "%s/weight/%d", topic, i + 1);
        
        // Concatenate the weight string with the topic
        char message[60]; // Adjust the size as needed
        snprintf(message, sizeof(message), "%s: %s", topicWithWeight, weightAsString);
        
        // Publish using the constructed message
        client.publish(topicWithWeight, message);


    }
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
