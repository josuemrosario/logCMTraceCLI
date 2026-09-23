#include <iostream>
#include <string>
#include <windows.h>
#include <sys/timeb.h>
#include <ctime>        
#include <cstdio>       

void obterDataHora(std::string &dataStr, std::string &horaStr) {
    struct _timeb timebuffer;
    _ftime(&timebuffer);

    time_t tempoSegundos = timebuffer.time;
    struct tm* infoTempo = localtime(&tempoSegundos);

    char bufferData[32];
    char bufferHora[32];

    strftime(bufferData, sizeof(bufferData), "%m-%d-%Y", infoTempo);
    sprintf(bufferHora, "%02d:%02d:%02d.%03d+000", 
            infoTempo->tm_hour, infoTempo->tm_min, infoTempo->tm_sec, timebuffer.millitm);

    dataStr = bufferData;
    horaStr = bufferHora;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Uso: logCMTraceCLI.exe \"Mensagem\" [\"Caminho\\Do\\Arquivo.log\"] [Tipo] [Componente]" << std::endl;
        return 1;
    }

    std::string mensagem   = argv[1];
    // Se o argumento 2 não for passado, definimos a string como vazia para indicar saída na console
    std::string caminhoLog = (argc > 2) ? argv[2] : "";
    std::string tipo       = (argc > 3) ? argv[3] : "1"; 
    std::string componente = (argc > 4) ? argv[4] : "indefinido";

    std::string dataStr, horaStr;
    obterDataHora(dataStr, horaStr);

    std::string linhaLog = "<![LOG[" + mensagem + "]LOG]!><time=\"" + horaStr + 
                           "\" date=\"" + dataStr + 
                           "\" component=\"" + componente + 
                           "\" context=\"\" type=\"" + tipo + 
                           "\" thread=\"1\" file=\"bat\">\r\n";

    // Se nenhum arquivo foi informado, imprime direto na console e encerra com sucesso
    if (caminhoLog.empty()) {
        std::cout << linhaLog;
        return 0;
    }

    // 1. CRIAÇÃO DE UM MUTEX GLOBAL NO SISTEMA OPERACIONAL
    HANDLE hMutex = CreateMutexA(NULL, FALSE, "Global\\LogCMTraceCLI_MutexUnico");
    
    if (hMutex != NULL) {
        DWORD waitResult = WaitForSingleObject(hMutex, 5000);
        
        if (waitResult != WAIT_OBJECT_0 && waitResult != WAIT_ABANDONED) {
            std::cerr << "Erro: Tempo limite esgotado aguardando o semaforo de log." << std::endl;
            CloseHandle(hMutex);
            return 1;
        }
    }

    // --- SEÇÃO CRÍTICA ---
    bool sucesso = false;
    
    HANDLE hFile = CreateFileA(
        caminhoLog.c_str(),
        FILE_APPEND_DATA,         
        FILE_SHARE_READ,          
        NULL,
        OPEN_ALWAYS,              
        FILE_ATTRIBUTE_NORMAL,
        NULL
    );

    if (hFile != INVALID_HANDLE_VALUE) {
        DWORD bytesEscritos = 0;
        BOOL bWrite = WriteFile(
            hFile,
            linhaLog.c_str(),
            (DWORD)linhaLog.length(),
            &bytesEscritos,
            NULL
        );

        CloseHandle(hFile);
        if (bWrite) {
            sucesso = true;
        }
    }

    // 2. LIBERAÇÃO OBRIGATÓRIA DO MUTEX
    if (hMutex != NULL) {
        ReleaseMutex(hMutex);
        CloseHandle(hMutex);
    }

    if (!sucesso) {
        std::cerr << "Erro: Nao foi possivel escrever no arquivo de log: " << caminhoLog << std::endl;
        return 1;
    }

    return 0;
}
