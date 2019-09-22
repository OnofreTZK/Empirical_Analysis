# Relatório técnico

## Sumário

+ **Introdução**
  + **Sobre o projeto** 
  + **Requisitos para reprodução e execução dos testes**
  + **Especificações da máquina utilizada**
  + **Compilação e execução**

+ **Análise**

## Introdução 

### Sobre o projeto

   O projeto de análise empírica tem como objetivo analisar o desempenho de determinados algoritmos de ordenação baseado no seu tempo de execução e número de interações em arranjos de tamanho `n` crescente. O projeto trabalha com seis cenários de amostras: ordem completamente aleatória, ordem não decrescente, ordem não crescente, arranjo 75% ordenado, arranjo 50% ordenado e arranjo 25% ordenado.

### Requisitos para reprodução e execução dos testes

* Sistema operacional: `linux`
* Aplicação auxiliar: `cmake` 
* Compilador: `g++`
* Versionador: `git`
* Gerar gráficos: `RStudio` . Caso deseje utilizar outro método atente-se apenas a formatação dos arquivos.

### Especificações da máquina utilizada

| Componente           | Modelo                                              |
| -------------------- | --------------------------------------------------- |
| Processador          | AMD Ryzen 7 1800X, Oito Núcleos, Cache 20MB, 3.6GHz |
| Placa mãe            | ASUS EX-A320M-Gaming Socket AM4 Chipset AMD A320    |
| Memória              | Memória RAM 24GB 3000 - 3200 MHz DDR4               |
| Sistema              | Ubuntu 18.04                                        |
| Linguaguem           | C++ 11                                              |
| Versão do compilador | g++ 7.4.0                                           |



### Compilação e execução

Para baixar o código na sua máquina:

```bash
$ git clone https://github.com/OnofreTZK/Empirical_Analysis.git

```

Para compilar:

``` bash
$ cmake -S . -Bbuild
$ cd build/
$ make
```

Para executar:

```bash
$ ./ea_driver <array_max_size> <initial_sample_size> <number_of_samples> <algorithm_ID>
```

* `<array_max_size>`: Tamanho máximo da amostra. 

* `<initial_sample_size>`: Tamanho da amostra inicial.

* `<number_of_samples> `: Número de amostras

* `<algorithm_ID>`: código do algoritmo de ordenação

  + **[0]** -- _Quick Sort_ 

  + **[1]** -- _Selection Sort_

  + **[2]** -- _Insertion Sort_

  + **[3]** -- _Bubble Sort_

  + **[4]** -- _Radix Sort_

  + **[5]** -- _Shell Sort_

  + **[6]** -- _Quick + Insertion_

  + **[7]** -- _Merge Sort_

    

O programa aceita até três algoritmos para análise em uma única execução, exemplo:

```bash
$ ./ea_drive 10000 5000 50 0 1 2

```

## Análise

Após a leitura e o processamento de argumentos, todas os dados são passadas para a função principal `execute_analysis` :

```c++
  // Exemplo de uma execução com 3 algoritmos.       

	std::cout << "\n>>>Starting " << data.sort_ID[algo1] << " analysis\n";
 
  execute_analysis( array[algo1], algo1, MAX, samples, init_sample, data );
 
  std::cout << "\n>>>Starting " << data.sort_ID[algo2] << " analysis\n";
 
  execute_analysis( array[algo2], algo2, MAX, samples, init_sample, data );
  
  std::cout << "\n>>>Starting " << data.sort_ID[algo3] << " analysis\n";

  execute_analysis( array[algo3], algo3, MAX, samples, init_sample, data );
  
  return EXIT_SUCCESS;
```



A partir dela os dados serão distribuidos para que o programa possa medir e guardar o que for necessário:

```c++
void execute_analysis( algorithms func, int algorithm_ID, long int max, 
                       long int samples, long int init_sample, DATA data )
{
    // Gerando um vetor completamente aleatório.
    long int * array = generate_array( max );

    // Variável para calcular a média do tempo
    //======================================================================
    double arithmetic_mean;// será utilizada a média aritmética progressiva
    //======================================================================

    data.alocate_vectors( samples );

    for( int type = 0; type < 6; type++ )
    {

        for( int iter_samples = 0; iter_samples < samples; iter_samples++)
        {

            arithmetic_mean = 0.0; // zerando a média

            for( int time_control = 0; time_control < 10; time_control++ )
            {
                type_array( array, type, data, max );

                // -- CONTADOR COMEÇA AQUI --
                std::chrono::steady_clock::time_point START = std::chrono::steady_clock::now();
                func( array, array + increase_array_control( max, samples, init_sample, iter_samples + 1 ) );
                std::chrono::steady_clock::time_point STOP = std::chrono::steady_clock::now();
                // -- CONTADOR TERMINA AQUI --

                auto timer = (STOP - START);

                //Cálculo da média progressiva.
                arithmetic_mean = arithmetic_mean + ( ( std::chrono::duration< double, std::milli > (timer).count() - arithmetic_mean )/(time_control+1) );

            }
            // Aloca de acordo com o número de amostras.
            long int sample = increase_array_control( max, samples, init_sample, iter_samples + 1 );

            // Guarda os valores para gerar o arquivo.
            data.set_values( sample, arithmetic_mean, iter_samples );
        }

        // Cria o arquivo.
        create_data_file( data, algorithm_ID, type );

    }

    delete[] array; // libera a memória.
}
```

