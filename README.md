# Checkpoint 02 - Vinheria Agnello 🍷

## Descrição do Projeto
Este projeto simula o sistema de monitoramento de condições ambientais para a Vinheria Agnello, uma loja tradicional de vinhos que busca expandir suas vendas online. O objetivo é criar uma experiência de usuário similar à do atendimento presencial, monitorando luminosidade, temperatura e umidade do ambiente de armazenamento dos vinhos.

## Objetivos
- Medir a temperatura e umidade do ambiente utilizando o sensor DHT11.
- Exibir os valores de temperatura, umidade e luminosidade em um display LCD.
- Sinalizar níveis críticos de temperatura e umidade através de LEDs e um buzzer.

## Requisitos
O projeto deve atender aos seguintes requisitos:

1. **Luminosidade:**
   - LED Verde aceso: Ambiente escuro.
   - LED Amarelo aceso e mensagem "Ambiente a meia luz" no display: Ambiente a meia luz.
   - LED Vermelho aceso, mensagem "Ambiente muito claro" no display e Buzzer ligado: Ambiente totalmente iluminado.

2. **Temperatura:**
   - Display informa "Temperatura OK" e mostra o valor da temperatura: Temperatura entre 10°C e 15°C.
   - LED Amarelo aceso e Buzzer ligado: Temperatura fora da faixa ideal.
   - Display informa "Temp. Alta" e mostra a temperatura: Temperatura acima de 15°C.
   - Display informa "Temp. Baixa" e mostra a temperatura: Temperatura abaixo de 10°C.

3. **Umidade:**
   - Display informa "Umidade OK" e mostra o valor da umidade: Umidade entre 50% e 70%.
   - LED Vermelho aceso e Buzzer ligado: Umidade fora da faixa ideal.
   - Display informa "Umidade. Alta" e mostra a umidade: Umidade acima de 70%.
   - Display informa "Umidade. Baixa" e mostra a umidade: Umidade abaixo de 50%.

4. **Geral:**
   - Os valores apresentados no display devem ser a média de pelo menos 5 leituras dos sensores, atualizados a cada 5 segundos.

## Componentes Utilizados
- Arduino IDE
- Sensor DHT11 (ou DHT22 no Wokwi)
- Display LCD
- LEDs (Verde, Amarelo, Vermelho)
- Buzzer
- Resistor
- Jumpers
