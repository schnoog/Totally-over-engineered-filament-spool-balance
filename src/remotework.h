
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

