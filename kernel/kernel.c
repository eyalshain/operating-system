void kmain() {
    char *video_memory = (char*) 0xb8000;
    char *message = "Hello Eyal! ";
    char message2[] = "Hello Eyal! ";

    // while (*message)
    // {
    //     *video_memory = *message;
    //     video_memory += 2;
    //     message++;
    // }

    for (int i = 0; message2[i] != '\0'; i++)
    {
        *video_memory = message2[i];
        video_memory += 2;
    }
    


    // *video_memory = 'G';
}