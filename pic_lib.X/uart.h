void init_UART1();
char get_char_UART1();
void put_char_UART1(char tr_simv);
void send_data_UART1(int data_tx);
void send_number_UART1(unsigned int digit);
void send_string_UART1 (char string[]);
void test_UART1(char send_byte, char send_str[], uint16_t send_number);


void init_UART2(); 
char get_char_UART2();
void put_char_UART2(char tr_simv);