#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <mosquitto.h>

#define MQTT_HOST "YOUR_EXTERNAL_SSH_IP_ADDRESS"
#define MQTT_PORT 1883

void on_connect(struct mosquitto *mosq, void *userdata, int result)
{
    if (result == 0)
    {
        printf("Connected to broker\n");
    }
    else
    {
        fprintf(stderr, "Connect failed\n");
        exit(EXIT_FAILURE);
    }
}

int main()
{
    struct mosquitto *mosq = NULL;
    const char *topic = "CHANGE_TO_YOUR_TOPIC_NAME";

    //Initialize the Mosquitto library
    mosquitto_lib_init();

    //Create a new Mosquitto client
    mosq = mosquitto_new(NULL, true, NULL);
    if (!mosq) 
    {
        fprintf(stderr, "Error: Out of memory.\n");
        return 1;
    }

    //Set the callback for connection
    mosquitto_connect_callback_set(mosq, on_connect);

    //Connect to the broker
    if (mosquitto_connect(mosq, MQTT_HOST, MQTT_PORT, 60) != MOSQ_ERR_SUCCESS)
    {
        fprintf(stderr, "Unable to connect to the broker.\n");
        return 1;
    }

    int choice;
    const char *one = "1";
    const char *two = "2";

    //Continuous loop for user input
    while (choice != 3) 
    {
        printf("Press 1 to publish 'On'\n");
        printf("Press 2 to publish 'OFF'\n");
        printf("Press 3 to exit\n");
        printf("Enter your choice: ");
	
        scanf("%d", &choice);

        //Process user input
        switch (choice) {
            case 1:
                mosquitto_publish(mosq, NULL, topic, 1, one, 0, false);
                printf("Published 'ON' to %s\n", topic);
		printf("published 'ON'")
                break;
            case 2:
                mosquitto_publish(mosq, NULL, topic, 1, two, 0, false);
                printf("Published 'OFF' to %s\n", topic);
                break;
            case 3:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please enter 1, 2, or 3.\n");
        }

        if (choice == 3)
        {
            printf("Exiting Program.\n");
        }
    }
    mosquitto_disconnect(mosq);
    mosquitto_destroy(mosq);
    mosquitto_lib_cleanup();

    return 0;
}
