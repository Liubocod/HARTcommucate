#ifndef LCD6029DRIVE_H
#define LCD6029DRIVE_H
void	LcdSetPage(unsigned char Page);
void	LcdSetColumn(unsigned char Column);
void	LcdWriteData(unsigned char data);
void	LcdDisplayInit(void);
void	DelayTeime(unsigned char TimeValure);
unsigned char LcdReadCommand(void);
void	LcdWriteCommand(unsigned char command);

unsigned char LcdReadData(void);




#endif
