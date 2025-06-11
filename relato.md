Relatório: 
# Relatório da Atividade 04 - Análise de Escalonamento

- Nome: João Pedro Dantas Magalhães
- Data:** 10 de junho de 2025

## 1. Objetivo

O objetivo desta prática foi analisar e comparar o comportamento de threads CPU-bound e I/O-bound em um ambiente Linux controlado por Docker. Utilizando ferramentas de monitoramento como `htop` e `perf`, a atividade buscou demonstrar como o escalonador do sistema operacional gerencia diferentes tipos de carga de trabalho.

## 2. Análise do Código Inicial

O programa inicial foi executado enquanto era monitorado pelo `htop` em um terminal separado.


**Observações:**
* **Threads CPU-bound:** Como esperado, as duas threads de cálculo intensivo consumiram quase 100% de dois núcleos de CPU durante toda a sua execução. Elas estavam constantemente no estado "Running" (R).
* **Threads I/O-bound:** Em contraste, as threads que simulavam I/O com `sleep(2)` ficaram a maior parte do tempo no estado "Sleeping" (S). Elas não consumiram recursos de CPU significativos, pois estavam apenas aguardando o término de uma operação (neste caso, o timer do `sleep`). Isso demonstra como o escalonador as "deixa de lado" para dar prioridade a tarefas que realmente precisam do processador.

## 3. Análise do Código Modificado com `perf stat`

O código foi modificado para incluir três threads de cada tipo e para realizar um cálculo de Pi mais intensivo. O programa modificado foi então analisado com a ferramenta `perf stat`.

**Saída do `perf stat`:**


**Análise dos Resultados:**
* A saída do `perf stat` mostra um alto número de `cycles` e `instructions`, confirmando a natureza CPU-bound da tarefa.
* O valor de `task-clock` (tempo de CPU efetivamente usado) é alto e próximo do `time elapsed` multiplicado pelo número de threads de CPU, indicando que o processador esteve ocupado a maior parte do tempo.


## 4. Conclusão

Esta atividade prática demonstrou de forma eficaz a diferença fundamental entre cargas de trabalho CPU-bound e I/O-bound e como o escalonador do Linux lida com elas. Ferramentas como `htop` e `perf` são essenciais para o diagnóstico de desempenho, permitindo visualizar em tempo real e coletar métricas detalhadas sobre o uso de recursos. A prática reforçou a importância de entender a natureza das tarefas de um software para otimizar seu desempenho e arquitetura.
