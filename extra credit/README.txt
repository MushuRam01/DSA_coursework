-----**USAGE INSTRUCTIONS**-----
IMPORTANT: ther emust be no additional text files apart from queries.txt or queries.txt.txt and those in /events_raw to aviod conflict
place folder events_raw in the same directory as src folder
place queries.txt.txt (yes that is how the file must be named) in the same directory as src
running clean.c will generate intermittent files that will be used for processing later.. please do not delete them till you have genrated final_output.txt
final_output.txt will be generated in the same directory as src

-----**how to start the pipeline**-----
after setting up events_raw and queries.txt.txt compile and run clean.c
NOTE!!; you do not need to compile heap.c 
compile and run queries.c 

-----**conversion pipeline**-----

START heap.c
clean tkaes all files in /events_raw and makes merged.txt
then merged .txt is used to create id_filtered.txt #invalid ids are removed
id_filtered.txt is used to create keys_corrected.txt #key values are corrected
keys_corrected is parsed to make ready_events.txt #duplicates are removed
ready_events is parsed to create cleaned_events.txt
STOP heap.c

START queries.c
queries.c takes queries.txt.txt and creates queries_corrected.txt # amkes funtion calls lowercase to avoid conflict
queries.c is runthrough a final_parse() funtion that :
    1.calls the funtions in heap.c
    2.generates a log file named final_output.txt
STOP queries.c

-----**AI/internet usage**-----
AI was occasionally used to help me debug largely pointer logic but no code was directly copy-pasted
Various sources from the internet were used and some help from online communities was taked to hep me build this