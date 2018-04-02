
void init_UART1();                              // UART module 1 initialization
char get_char_UART1();                          // receive 8 bits (1 byte)
void put_char_UART1(char tr_simv);              // transmit 8 bits (1 byte)
void send_data_UART1(int data_tx);              // transmit 16 bits (2 bytes)
void send_string_UART1 (char *string);          // transmit string
void send_number_UART1(unsigned int digit);     // transmit number as sequence of digits

