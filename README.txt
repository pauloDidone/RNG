Este repositório contém o código que implementa 3 geradores de números pseudo-aleatórios baseados em registradores de deslocamento. Cada gerador salva um arquivo com a sequência de números binários gerados. Cada sequência gerada por esses geradores será testada estatísticamente a fim de verificar qual o nível de aleatoriedade. As ferramentas utilizadas nos testes estão disponíveis em:

http://csrc.nist.gov/groups/ST/toolkit/rng/documentation_software.html

http://www.fourmilab.ch/random/

Para utilizar os geradores, basta compilar o arquivo prng.cpp utilizando o compilador g++ (Ubuntu) e posteriormente executar o binário gerado. Após a execução, 3 arquivos contendo as sequencias geradas de cada gerador estarão disponíveis no mesmo local do executável, que são o lfsr_f.txt, lfsr_g.txt e mTwister.txt, representando as saídas dos geradores LFSR Fibonacci, LFSR Galois e Mersene Twister respectivamente. posteriromente esses arquivos servirão como entradas para as ferramentas de análises estatisticas citadas anteriormente. 



