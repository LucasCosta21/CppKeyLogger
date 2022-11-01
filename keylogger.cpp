#include <stdio.h>
#include <windows.h>
#include <iostream>

int main()
{
    DWORD        mode;
    INPUT_RECORD event;

    FILE* myfile = fopen( "log.txt", "w" );
    HANDLE hstdin = GetStdHandle( STD_INPUT_HANDLE );
    GetConsoleMode( hstdin, &mode );
    SetConsoleMode( hstdin, 0 );
    
    //ShowWindow(GetConsoleWindow(), SW_HIDE);
    
    bool capsLockLigado = (GetKeyState(VK_CAPITAL) & 0x0001) != 0;
    bool numLockLigado = (GetKeyState(VK_NUMLOCK) & 0x0001) != 0;
    
	int correcaoCap = capsLockLigado ? 0 : 32;
	
    while (!done)
    {
        if (WaitForSingleObject( hstdin, 0 ) == WAIT_OBJECT_0)
        {
            ReadConsoleInput( hstdin, &event, 1, &count );

            if ((event.EventType == KEY_EVENT)
            &&  !event.Event.KeyEvent.bKeyDown)
                switch (event.Event.KeyEvent.wVirtualKeyCode)
                {
                	case VK_CAPITAL:
                        fprintf( myfile, "[CAPS]");
                        printf( "[CAPS]" );
                        capsLockLigado = !capsLockLigado;
                        correcaoCap = capsLockLigado ? 0 : 32;
                        break;
                    case VK_NUMLOCK:
                        fprintf( myfile, "[NUM_LOCK]");
                        printf( "[NUM_LOCK]" );
                        numLockLigado = !numLockLigado;
                        break;
                    case VK_ESCAPE:
                        fprintf( myfile, "[ESC]");
                        printf( "[ESC]" );
                        break;
                    case VK_BACK:
                        fprintf( myfile, "[BS]");
                        printf( "[BS]" );
                        break;
                    case VK_TAB:
                        fprintf( myfile, "[TAB]");
                        printf( "[TAB]" );
                        break;
                    case VK_RETURN:
                        fprintf( myfile, "[ENTER]");
                        printf( "[ENTER]" );
                        break;
                    case VK_SHIFT:
                        fprintf( myfile, "[SHIFT]");
                        printf( "[SHIFT]" );
                        break;
                    case VK_CONTROL:
                        fprintf( myfile, "[CONTROL]");
                        printf( "[CONTROL]" );
                        break;
                    case 186:
                        std::cout << char(capsLockLigado ? 128 : 135);
                        break;
                    default:
                    	if(event.Event.KeyEvent.wVirtualKeyCode >= 65 && event.Event.KeyEvent.wVirtualKeyCode <= 90)
						{
							std::cout << char(event.Event.KeyEvent.wVirtualKeyCode + correcaoCap);
						} 
						// Registro de números do numpad, caso o NumLock esteja ativado
						else if(numLockLigado)
						{
							if(event.Event.KeyEvent.wVirtualKeyCode >= 97 && event.Event.KeyEvent.wVirtualKeyCode <= 105)
							{
								std::cout << char(event.Event.KeyEvent.wVirtualKeyCode - 48);
							}
						}
						
                }
        }
    }

    fclose( myfile );
    SetConsoleMode( hstdin, mode );
    return 0;
}
   
