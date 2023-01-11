#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <psapi.h>

void PrintProcessNameAndID( DWORD processID );

int main()
{
  // Get the list of process identifiers.
  DWORD aProcesses[1024], cbNeeded, cProcesses;
  unsigned int i;

  if ( !EnumProcesses( aProcesses, sizeof(aProcesses), &cbNeeded ) )
  {
      printf("\r\n枚举进程错误");
  }else
  {
    // Calculate how many process identifiers were returned.
    cProcesses = cbNeeded / sizeof(DWORD);
    // Print the name and process identifier for each process.
    for ( i = 0; i < cProcesses; i++ )
    {
        if( aProcesses[i] != 0 )
        {
            PrintProcessNameAndID( aProcesses[i] );
        }
    }
  }
  system("pause");
}


void PrintProcessNameAndID( DWORD processID )
{
    TCHAR inneedName[MAX_PATH] = TEXT("r5apex.exe");
    TCHAR szFileName[MAX_PATH] = TEXT("unknown");
    TCHAR szBaseName[MAX_PATH] = TEXT("<unknown>");

    DWORD iBaseName=0;

    // Get a handle to the process.
    HANDLE hProcess = OpenProcess( PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processID );

    // Get the process name.c
    if (NULL != hProcess )
    {
                  if ( processID ==4000)
            {
              printf("----------------------");
            }
            GetModuleFileNameEx( hProcess, NULL, szFileName, sizeof(szFileName)/sizeof(TCHAR) );
            for (size_t i = 0; i < MAX_PATH; i++)
            {
              if ( szFileName[i] != TEXT('\\') )
              {
                szBaseName[iBaseName]=szFileName[i];
                iBaseName=iBaseName+1;
              }else
              {
                iBaseName=0;
              }
            }
            if (szBaseName==inneedName)
            {
              printf("----------------------");
            }
            
            printf("\r\n>>>>  %-36s%-15ld[%s]\r\n",szBaseName,processID,szFileName);
    }
    // Print the process name and identifier.
    

     //_tprintf( TEXT("%s  (PID: %u)\n"), szProcessName, processID );
    // Release the handle to the process.
    CloseHandle( hProcess );
}