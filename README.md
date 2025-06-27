# 📞 Sistema de Call Center com Prioridades

## 👥 Autores
- Felyppe Marcelo da Silva
- Henrique Meneses dos Santos Corrêa  
- Paulo Roberto Gomes Barroso Schiochet  
- Thiago Tanaka Peczek 

---

## 🧾 Descrição

Este projeto simula um sistema de atendimento de chamadas telefônicas com base em **prioridades** (alta, média e baixa). As chamadas são organizadas em **filas**, e os atendimentos são registrados em uma **pilha de histórico**, com geração de estatísticas e relatório final.

---

## 🎯 Funcionalidades

- Inserção de chamadas com nome, motivo e prioridade
- Visualização das filas de atendimento por prioridade
- Atendimento da próxima chamada (ordem: alta > média > baixa)
- Registro do histórico de atendimentos
- Cálculo de tempo médio de espera por prioridade
- Geração de relatório final detalhado

---

## 🗂️ Estrutura do Projeto

├── chamadas.h / chamadas.c → Manipulação de filas e chamadas
├── atendimento.h / atendimento.c → Lógica de atendimento e estatísticas
├── historico.h / historico.c → Gerenciamento da pilha de histórico
├── main.c → Menu principal e controle do sistema

---

## ⚙️ Compilação

Compile e execute com o comando:

gcc main.c chamadas.c atendimento.c historico.c -o atendimento
./atendimento

---

📌 Observações

- O tempo de espera de cada chamada é simulado aleatoriamente entre 1 e 10 minutos.
- O histórico é mantido em uma pilha (último atendimento no topo).
- O sistema roda apenas em tempo de execução (sem persistência em arquivos).

---

🧹 Finalização
Ao gerar o relatório final, o programa libera toda a memória alocada pelo histórico.
