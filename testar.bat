@echo off
:: Configura a página de código do console para UTF-8 para evitar problemas com acentos no CMD
chcp 65001 >nul

:: Nome do executável compiado (ajuste se mudou o nome do arquivo)
set "EXE_NAME=logCMTraceCLI.exe"
:: Nome do arquivo de log que será criado para o teste
set "LOG_FILE=teste_completo.log"

echo =======================================================
echo    INICIANDO TESTES DO LOGGER COMPATÍVEL COM CMTRACE
echo =======================================================
echo.

:: Verifica se o executável existe na pasta
if not exist "%EXE_NAME%" (
    color 0C
    echo [ERRO] O arquivo %EXE_NAME% nao foi encontrado nesta pasta!
    echo Certifique-se de que o .exe compilado está ao lado deste arquivo .bat.
    echo.
    pause
    exit /b
)

:: Apaga o log de testes anterior, se existir, para começar limpo
if exist "%LOG_FILE%" del "%LOG_FILE%"

echo [+] 1. Testando argumentos mínimos (Mensagem e Caminho apenas)...
:: Deve assumir Tipo="1" (Branco) e Componente="ScriptBAT" automaticamente
%EXE_NAME% "Esta é uma mensagem simples usando os valores padrões do programa." "%LOG_FILE%"
timeout /t 1 >nul

echo [+] 2. Testando Tipo 1 - Informativo (Com componente personalizado)...
:: Forçando o tipo 1 e definindo o componente como "Modulo_A"
%EXE_NAME% "Inicialização do sistema concluída com sucesso." "%LOG_FILE%" 1 "Modulo_A"
timeout /t 1 >nul

echo [+] 3. Testando Tipo 2 - Aviso / Warning (Fica Amarelo no CMTrace)...
:: Forçando o tipo 2 e definindo o componente como "Segurança"
%EXE_NAME% "Aviso: O espaço temporário em disco está acima de 85%%." "%LOG_FILE%" 2 "Seguranca"
timeout /t 1 >nul

echo [+] 4. Testando Tipo 3 - Erro Crítico / Error (Fica Vermelho no CMTrace)...
:: Forçando o tipo 3 e definindo o componente como "BancoDados"
%EXE_NAME% "Erro Crítico: Falha na conexão com o servidor de banco de dados." "%LOG_FILE%" 3 "BancoDados"
timeout /t 1 >nul

echo.
echo =======================================================
echo               TESTES CONCLUÍDOS COM SUCESSO!
echo =======================================================
echo O arquivo "%LOG_FILE%" foi gerado na pasta atual.
echo.
echo Abra o arquivo "%LOG_FILE%" no CMTrace para conferir as cores:
echo  - Linhas 1 e 2 devem estar Normais (Fundo Branco)
echo  - Linha 3 deve estar em AMARELO (Aviso)
echo  - Linha 4 deve estar em VERMELHO (Erro).
echo =======================================================
echo.
pause
