# LogCMTraceCLI

Uma ferramenta de linha de comando leve desenvolvida em C/C++ para gerar arquivos de log no formato padrão da Microsoft (compatível com CMTrace e CMTraceOpen). Ideal para ser integrada em scripts de automação (como arquivos .bat, .cmd ou .ps1).

---

## Como Usar

A sintaxe básica para execução do executável é:

```cmd
logCMTraceCLI.exe "Sua mensagem de log" "Caminho\Do\Arquivo.log" [Tipo] [Componente]
```

### Descrição dos Argumentos

| Argumento | Descrição | Obrigatório? |
| :--- | :--- | :--- |
| **1º** | A mensagem que será registrada no log. | **Sim** |
| **2º** | O caminho completo ou relativo do arquivo de log. | **Sim** |
| **3º** | O **Tipo** de severidade do log (1, 2 ou 3). | Não (Padrão: 1) |
| **4º** | O **Componente** (módulo ou script de origem). | Não (Padrão: CLI) |

---

## Tipos de Log e Severidade

O visualizador CMTrace utiliza o código de tipo para colorir as linhas automaticamente, facilitando o diagnóstico:

*   **1 — Informação (Normal)**
    *   *Visual:* Fundo branco.
    *   *Uso:* Eventos rotineiros ou transações bem-sucedidas (ex: "Conexão estabelecida").
*   **2 — Aviso (Warning)**
    *   *Visual:* Destacado com fundo amarelo.
    *   *Uso:* Situações atípicas que requerem atenção, mas não pararam a execução (ex: "Espaço em disco baixo").
*   **3 — Erro (Error)**
    *   *Visual:* Destacado com fundo vermelho.
    *   *Uso:* Falhas críticas ou interrupções de fluxo (ex: "Arquivo de configuração não encontrado").

---

## Compilando e Testando

O programa foi estruturado para obter máxima compatibilidade com o Windows utilizando o **Dev-C++**.

1. Abra o projeto no **Dev-C++**.
2. Compile o código-fonte gerando o executável.
3. Execute o arquivo `testar.bat` incluído no repositório.

Ao final, o arquivo `teste_completo.log` será gerado na raiz do projeto, pronto para inspeção.

---

## Sobre o CMTrace

Atualmente, o CMTrace clássico da Microsoft não é mais distribuído oficialmente de forma standalone. Para visualizar os logs gerados em ambientes modernos, utilize o **CMTraceOpen**:

*   Repositório Oficial: [https://github.com/adamgell/cmtraceopen](https://github.com/adamgell/cmtraceopen)

---

## Observações

*   Projeto desenvolvido com o auxílio de Inteligência Artificial (Google Gemini).