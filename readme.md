# LOGCMTRACECLI

Os logs da Microsoft usam um padrão específico para serem lidos pelo aplicativo **CMTrace** (ou alternativas como o **CMTraceOpen**). Este aplicativo de linha de comando foi desenvolvido para gerar esses tipos de logs diretamente via CLI, permitindo seu uso integrado em scripts (como arquivos `.bat` ou `.ps1`).

## Compilando e Testando

O programa foi gerado com auxílio de inteligência artificial e foi estruturado/compilado usando o **Dev-C++** para obter o máximo de compatibilidade com o Windows.

Para compilar o projeto:
1. Abra o projeto no **Dev-C++**.
2. Compile o programa.
3. Execute o arquivo `testar.bat`.

Ao final, é esperado que o arquivo `teste_completo.log` seja gerado na raiz do projeto, pronto para ser aberto pelo visualizador de logs.

## Sobre o CMTrace

Atualmente, o CMTrace tradicional da Microsoft não é mais oferecido de forma standalone oficial, mas para testes e ambientes modernos é possível utilizar o **CMTraceOpen**:

* Repositório oficial: [https://github.com/adamgell/cmtraceopen](https://github.com/adamgell/cmtraceopen)

   
## Observações

 Aplicativo foi gerado pelo Google Gemini