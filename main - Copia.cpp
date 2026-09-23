#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <sys/timeb.h>
#include <ctime>       
#include <cstdio>      

// Função compatível com MinGW GCC para obter a data e hora no formato CMTrace
void obterDataHora(std::string &dataStr, std::string &horaStr) {
    struct _timeb timebuffer;
    _ftime(&timebuffer); // Versão ANSI estável no MinGW

    time_t tempoSegundos = timebuffer.time;
    struct tm* infoTempo = localtime(&tempoSegundos); // Versão padrão ANSI (não trava no GCC)

    char bufferData[32];
    char bufferHora[32];

    // Formato da Data: MM-dd-yyyy
    strftime(bufferData, sizeof(bufferData), "%m-%d-%Y", infoTempo);
    
    // Formato da Hora com Milissegundos e Fuso Horário Falso (+000) usando sprintf padrão
    sprintf(bufferHora, "%02d:%02d:%02d.%03d+000", 
            infoTempo->tm_hour, infoTempo->tm_min, infoTempo->tm_sec, timebuffer.millitm);

    dataStr = bufferData;
    horaStr = bufferHora;
}

int main(int argc, char* argv[]) {
    // Validação dos argumentos mínimos obrigatórios
    if (argc < 3) {
        std::cout << "Uso: logger_cmtrace.exe \"Mensagem\" \"Caminho\\Do\\Arquivo.log\" [Tipo: 1, 2, 3] [Componente]" << std::endl;
        return 1;
    }

    std::string mensagem   = argv[1];
    std::string caminhoLog = argv[2];
    std::string tipo       = (argc > 3) ? argv[3] : "1"; 
    std::string componente = (argc > 4) ? argv[4] : "indefinido";

    std::string dataStr, horaStr;
    obterDataHora(dataStr, horaStr);

    // Monta a estrutura exata exigida pelo CMTrace
    std::string linhaLog = "<![LOG[" + mensagem + "]LOG]!><time=\"" + horaStr + 
                           "\" date=\"" + dataStr + 
                           "\" component=\"" + componente + 
                           "\" context=\"\" type=\"" + tipo + 
                           "\" thread=\"1\" file=\"bat\">";

    // Abre o arquivo forçando o uso de .c_str() para corrigir o erro da linha 57
    std::ofstream arquivo;
    arquivo.open(caminhoLog.c_str(), std::ios_base::app);
    
    if (arquivo.is_open()) {
        arquivo << linhaLog << std::endl;
        arquivo.close();
    } else {
        std::cerr << "Erro: Nao foi possivel abrir ou criar o arquivo de log: " << caminhoLog << std::endl;
        return 1;
    }

    return 0;
}

