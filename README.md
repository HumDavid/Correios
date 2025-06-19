# 📦 Sistema de Gerenciamento de Entregas

Projeto final da disciplina de **Programação e Algoritmo**, desenvolvido individualmente em linguagem C.

Este sistema permite o **gerenciamento completo de entregas, funcionários, veículos e clientes**, com persistência de dados em arquivos `.txt` e interface interativa via terminal.

---

## 🚀 Funcionalidades Principais

### 📬 Entregas
- Cadastrar, visualizar, editar e deletar entregas
- Concluir entregas com registro no relatório
- Associação com funcionário, cliente e veículo

### 👤 Funcionários
- Cadastro com validação de ID
- Visualização, edição e remoção

### 🚚 Veículos
- Cadastro com escolha de tipo (bicicleta, moto, van, caminhão, etc.)
- Capacidade validada por tipo de veículo
- Edição e deleção

### 🏠 Clientes
- Cadastro com endereço completo (estado, cidade, bairro, rua e número)
- Escolha do tipo de serviço (econômico, padrão, premium)
- Visualização, edição e deleção

### 📊 Relatórios
- Registro completo das entregas concluídas
- Informações associadas: entrega, funcionário, veículo, cliente, origem, destino e tempo total

---

## 🧭 Navegação no Menu

O menu principal oferece 5 seções:

1: Entregas
2: Funcionários
3: Veículos
4: Clientes
5: Relatórios
6: Sair

Cada seção permite operações específicas como cadastro, visualização, edição, remoção e ações especiais (como conclusão de entrega ou geração de relatório).

---

## 🗂️ Estrutura dos Dados

Os dados são armazenados nos seguintes arquivos, com separação por `|`:

- `Entregas.txt`
- `Funcionarios.txt`
- `Veiculos.txt`
- `Clientes.txt`
- `Relatorio.txt`

Os dados são manipulados diretamente por leitura e escrita nesses arquivos.

---

## ⏳ Tempo de Desenvolvimento

O projeto foi desenvolvido em cerca de 40 horas, distribuídas ao longo de 5 dias:

- Dia 1 (quinta): 8h
- Dia 2 (sexta): 9h30
- Dia 3 (sábado): 11h30
- Dia 4 (domingo): 11h30
- Dia 5 (segunda): 1h

---

## 📝 Observações

- Projeto desenvolvido inteiramente por um único aluno, sem auxílio de bibliotecas externas.
- O código foi mantido em um único arquivo .c por motivo de prazo curto e foco em funcionalidade.
- Pode ser aprimorado com modularização, separação em múltiplos arquivos e uso de headers.
- Toda a entrada/saída é feita via terminal.

---

## 📎 Requisitos Técnicos Demonstrados

- Estruturas (struct)
- Manipulação de arquivos em C
- Lógica de menus e controle de fluxo
- Validação de entrada do usuário
- Modularidade funcional
- Uso prático de arrays e strings
