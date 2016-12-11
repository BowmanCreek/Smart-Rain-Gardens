# Smart-Rain-Gardens

How to use:

For this software, we were using version Arduino version 1.6.9.  If the version you install does not compile the code, you may want to try using this version.

1)
Choose clone or download.  If you download, when you extract, save under C:\Users\Documents\Arduino or wherever Arduino has been installed on your computer.

2)
Each sketch will require a notebook folder, when prompted let Arduino make it for you.


Programs included:

Sample Time:  Shows an example of how to use the function "millis" to record data at certain time intervals.


Note: The main code for data monitoring still contains use of external UNIXTIME libraries for the program GardenSDNOXbee.ino.  Those should be transitioned to using the function millis() similar to how FInalPresentationDataCollection.ino looks.  The external UNIXtime libraries are not needed.  As of now, there is no official timestamp, so that must be recorded at the start and end of executing the program, and used to interpret data based on intervals.
