# Projeto: Controle de LEDs e Buzzer com Raspberry Pi Pico

Este projeto demonstra como controlar LEDs e um buzzer utilizando um Raspberry Pi Pico. Ele implementa funcionalidades como acender LEDs, desligá-los, e emitir sons com o buzzer. O código foi simulado usando o [Wokwi](https://wokwi.com/), uma poderosa ferramenta de prototipagem online. O projeto também utiliza um diagrama em formato JSON para configurar os componentes.

---

## 📜 Funcionalidades

- **Controle de LEDs:** Permite ligar e desligar LEDs individuais (verde, azul e vermelho) ou todos ao mesmo tempo.
- **Controle de Buzzer:** Emite um som por 2 segundos quando acionado.
- **Comando de Reinício:** Reinicia o microcontrolador via software.
- **Ajuda:** Lista todos os comandos disponíveis.

---

## 🚀 Tecnologias Utilizadas

- **Raspberry Pi Pico SDK:** Framework oficial para desenvolvimento em C/C++ no Raspberry Pi Pico.
- **Wokwi:** Simulador online utilizado para testar o projeto antes da implementação física.
- **CMake:** Ferramenta de gerenciamento de build para compilar o projeto.
- **Diagrama JSON do Wokwi:** Configuração do hardware do projeto no simulador.

---

## 🛠️ Componentes

### Hardware:

- 1x Raspberry Pi Pico
- 3x LEDs (verde, azul e vermelho)
- 1x Buzzer
- Resistores adequados para os LEDs e o buzzer
- Fios de conexão

### Configuração JSON (Wokwi):

```json
{
  "version": 1,
  "author": "Seu Nome",
  "components": [
    {
      "type": "pico",
      "id": "pico",
      "x": 150,
      "y": 100
    },
    {
      "type": "led",
      "id": "led_green",
      "x": 200,
      "y": 80,
      "color": "green",
      "pin": 11
    },
    {
      "type": "led",
      "id": "led_blue",
      "x": 200,
      "y": 120,
      "color": "blue",
      "pin": 12
    },
    {
      "type": "led",
      "id": "led_red",
      "x": 200,
      "y": 160,
      "color": "red",
      "pin": 13
    },
    {
      "type": "buzzer",
      "id": "buzzer",
      "x": 200,
      "y": 200,
      "pin": 21
    }
  ]
}
```

> Este diagrama JSON configura os componentes no simulador Wokwi.

---

## 📋 Comandos Disponíveis

| Comando     | Descrição                                           |
|-------------|---------------------------------------------------|
| `LED_GREEN` | Liga o LED verde                                   |
| `LED_BLUE`  | Liga o LED azul                                    |
| `LED_RED`   | Liga o LED vermelho                                |
| `ALL_ON`    | Liga todos os LEDs (branco)                        |
| `ALL_OFF`   | Desliga todos os LEDs                              |
| `BUZZER`    | Aciona o buzzer por 2 segundos                     |
| `REBOOT`    | Reinicia o microcontrolador                        |
| `HELP`      | Exibe a lista de comandos disponíveis              |

---

## 💻 Como Executar

1. **Clone o Repositório:**
   ```bash
   git clone https://github.com/Marques-svnt/tarefa02_1401_sub2.git
   cd tarefa02_1401_sub2
   ```

2. **Configure o SDK do Raspberry Pi Pico:**
   Certifique-se de que o SDK está configurado corretamente em seu ambiente. Consulte a [documentação oficial](https://github.com/raspberrypi/pico-sdk) para mais detalhes.

3. **Compile o Projeto:**
   ```bash
   mkdir build
   cd build
   cmake ..
   make
   ```

4. **Carregue o Código no Pico:**
   - Conecte o Pico ao computador em modo de boot (pressionando o botão BOOTSEL ao conectar).
   - Copie o arquivo `.uf2` gerado para o dispositivo montado.

5. **Teste no Wokwi (Opcional):**
   - Abra o Wokwi e importe o diagrama JSON.
   - Carregue o código no simulador.

---

## Demonstração no YouTube

Confira a demonstração completa deste projeto no YouTube: [Demonstração do Projeto](https://www.youtube.com/watch?v=Vkqzke5KTdE)

## 📌 Notas Finais

Este projeto serve como base para aplicações mais complexas no Raspberry Pi Pico. Ele pode ser expandido para incluir sensores, displays ou controle remoto.

Contribuições e sugestões são bem-vindas! # tarefa02_1401_sub2
Tarefa 2 da aula síncrona do dia 14/01 do subgrupo 2 - Grupo 0
