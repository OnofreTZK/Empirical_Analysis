# Relatório técnico

## Sumário

+ **Introdução**
  + **Sobre o projeto** 
  + **Requisitos para reprodução e execução dos testes**
  + **Especificações da máquina utilizada**
  + **Compilação e execução**

+ **Análise**
  + **Processando as linhas de comando**
  + **Funções Principais** 
    + `generate_array`
    + `increase_array_control`
    + `Cálculo da média aritmética progressiva`
    + `type_array `

* **Algoritmos**
  	+  _**Quick Sort**_
  	+  _**Insertion Sort**_

## Introdução 

### Sobre o projeto

   O projeto de análise empírica tem como objetivo analisar o desempenho de um conjunto de algoritmos de ordenação baseado no seu tempo de execução e número de interações em arranjos de tamanho `n` crescente. O projeto trabalha com seis cenários de amostras: ordem completamente aleatória, ordem não decrescente, ordem não crescente, arranjo 75% ordenado, arranjo 50% ordenado e arranjo 25% ordenado.

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



### Processando as linhas de comando

Após a leitura e o processamento de argumentos, todos os dados são passadas para a função principal `execute_analysis` :

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



### Funções principais

* **`generate_array`**

```c++ 
//=======================================================================================
// aloca e preenche o vetor com números em um intervalo de [0, <array_max_size>) 
//=======================================================================================
long int generate_numbers( long int range )
{
      std::random_device seed;

      std::mt19937_64 gen( seed() );
      // aleatoriedade com probabilidade linear.
      std::uniform_int_distribution<long int> distr(0, range); 

      return distr( gen );
}


long int * generate_array( long int max )
{
  	// alocação utilizando a entrada do usuário.
    long int * array = new long int [max];

    for ( int i = 0; i < max; i++ )
    {
        array[i] = generate_numbers(max); 
    }

    return array;
}
//====================================================================================
```

+ **`increase_array_control`**

```c++
//====================================================================================
// Crescimento linear das amostras utilizando P.A. ( <init_sample>, <array_max_size> )
//====================================================================================
long int increase_array_control( long int max, long int samples, long int init_sample, int index )
{
    //calculando o 'r'( razão) progressão aritmética.
    long int reason = ( max - init_sample )/ samples;

    return init_sample + (( index - 1 ) * reason);

}
//====================================================================================
```

O método de crescimento da `amostra inicial`  ao `tamanho máximo` é linear

  Fórmula :

​                    $amostra_{n}$ = $amostra_{1}$ $+$ $(n -1)reason$ 



 `n` = índice da amostra.



`reason` =  $\frac{amostra_{m} - amostra_{0}}S$

`S` = número de amostras.



+ **Cálculo da média aritmética progressiva**

```c++
arithmetic_mean = arithmetic_mean + ( ( std::chrono::duration< double, std::milli > (timer).count() - arithmetic_mean )/(time_control+1) );
```

Buscando o máximo de precisão cada amostra é analisada 10 vezes e o tempo guardado é a média de todas as execuções. Com o intuito de evitar erros de arredondamento o programa utiliza a seguinte fórmula:

​                    

$M_{k}$ =  $M_{k-1}$ $+$ $\frac{x_{k} - M_{k-1}}k$ 



+ **`type_array`** 

 ```c++
//==========================================================================
// Seleciona baseado no laço qual amostra deve ser gerada para análise.
//==========================================================================
void type_array( long int * array ,int type, DATA data, long int max )
{

        switch( type )
        {
            case 0 :
                std::cout << "\nTEST " << type+1 << " -- " << data.typesample[type] << "\n";
                random_array( array, array + max, max );
                break;
            case 1 :
                std::cout << "\nTEST " << type+1 << " -- " << data.typesample[type] << "\n";
                ascending_sorting( array, array + max );
                break;
            case 2 :
                std::cout << "\nTEST " << type+1 << " -- " << data.typesample[type] << "\n";
                descending_sorting( array, array + max );
                break;
            case 3 :
                std::cout << "\nTEST " << type+1 << " -- " << data.typesample[type] << "\n";
                ascending_sorting( array, array + max );
                partial_sorting( array, array + max, 25 );
                break;
            case 4 :
                std::cout << "\nTEST " << type+1 << " -- " << data.typesample[type] << "\n";
                ascending_sorting( array, array + max );
                partial_sorting( array, array + max, 50);
                break;
            case 5 :
                std::cout << "\nTEST " << type+1 << " -- " << data.typesample[type] << "\n";
                ascending_sorting( array, array + max );
                partial_sorting( array, array + max, 75 );
                break;
            default:
                std::cout << "\nHow?\n";
                break;
        }
}
//==========================================================================
 ```



## Algoritmos



### Quick Sort

* É o método de ordenação interna mais rápido que se conhece para uma ampla variedade de situações.

* Complexidade no pior caso: $O(n²)$ 

* Complexidade no melhor e médio caso: $O(n log n)$ 

* Não é estável.

* Estratégia:  **_dividir e conquistar_**

* Funcionamento:

  ```
  procedimento QuickSort(X[], IniVet, FimVet)
  var
   i, j, pivo, aux
  início
     i <- IniVet
     j <- FimVet
     pivo <- X[(IniVet + FimVet) div 2]
     enquanto(i <= j)
      |      enquanto (X[i] < pivo) faça
      |       |   i <- i + 1
      |      fimEnquanto
      |      enquanto (X[j] > pivo) faça
      |       |   j <- j - 1
      |      fimEnquanto
      |      se (i <= j) então
      |       |   aux  <- X[i]
      |       |   X[i] <- X[j]
      |       |   X[j] <- aux
      |       |   i <- i + 1
      |       |   j <- j - 1
      |      fimSe
     fimEnquanto
     se (IniVet < j) então
      |  QuickSort(X, IniVet, j)
     fimSe
     se (i < FimVet) então
      |  QuickSort(X, i, FimVet)
     fimse
  fimprocedimento
  ```



##### Gráficos:

`Cenário`: _Arranjo completamente aleatório_

<img src="data/quick/quick_sort_Full_random.png" alt="quick_sort_Full_random" style="zoom: 150%;" />

Os picos representam os momentos em que as amostras tendem ao pior caso, porém a eficiência do algoritmo é evidente.



`Cenário`:  _Arranjo em ordem não decrescente_

<img src="data/quick/quick%20sort_non-descending%20order.png" alt="quick sort_non-descending order" style="zoom:150%;" />

Aqui temos um exemplo de pior caso demonstrado com o pivô igual a `last - 1` e todos os elementos menores à sua esquerda. Com a limitação da máquina não foi possível analisar amostras muito maiores para melhor visualização da curva da parábola. 



`Cenário`:  _Arranjo em ordem não crescente_

<img src="data/quick/quick%20sort_non-ascending%20order.png" alt="quick sort_non-ascending order" style="zoom:150%;" />

Assim como o gráfico anterior, esse demonstra outro exemplo de pior caso com o pivô igual a `first`  e todos os elementos maiores à sua direita.



`Cenário`:  _Arranjo 75% ordenado_

<img src="data/quick/quick%20sort_sorted:%2075%25.png" alt="quick sort_sorted: 75%" style="zoom:150%;" />



`Cenário`:  _Arranjo 50% ordenado_ 

<img src="data/quick/quick%20sort_sorted:%2050%25.png" alt="quick sort_sorted: 50%" style="zoom:150%;" />



`Cenário`:  _Arranjo 25% ordenado_

<img src="data/quick/quick%20sort_sorted:%2025%25.png" alt="quick sort_sorted: 25%" style="zoom:150%;" />

`Comparação`:  _Arranjos parcialmente ordenados_

![comparação quick 25,50,75](data/quick/compara%C3%A7%C3%A3o%20quick%2025,50,75.png)

Pela observação comparativa dos 3 gráficos é notória a queda desempenho do algoritmo quando a divisão do vetor é desbalanceada, com isso pode-se concluir que o quick sort não é a melhor opção para arranjos parcialmente ordenados.





### Insertion Sort

* Ordenação por inserção 

* Percorre um vetor de elementos da esquerda para a direita e à medida que avança vai ordenando os elementos à esquerda

* Complexidade no melhor caso:  $ O(n)$

* Complexidade no pior caso: $ O(n²) $ 

*  Método de ordenação estável.

* Funcionamento:

  ```
  FUNÇÃO INSERTION_SORT (A[], tamanho)
          VARIÁVEIS
                  i, j, eleito
          PARA i <- 1 ATÉ (tamanho-1) FAÇA
                  eleito <- A[i];
                  j <- i-1;
                  ENQUANTO ((j>=0) E (eleito < A[j])) FAÇA
                            A[j+1]:= A[j];
  # Elemento de lista numerada
                            j:=j-1;
                  FIM_ENQUANTO
                  A[j+1] <- eleito;
          FIM_PARA
  FIM
  ```

   

**Gráficos** :



`Cenário`:  _Arranjo completamente aleatório_

<img src="data/insertion/insertion%20sort_Full%20random.png" alt="insertion sort_Full random" style="zoom:150%;" />

Em um arranjo sem ordem total o algoritmo não tem eficiência e deve ser evitado para amostras muito grandes 



`Cenário`:  _Arranjo em ordem não decrescente_

<img src="data/insertion/insertion%20sort_non-descending%20order.png" alt="insertion sort_non-descending order" style="zoom:150%;" />

Visualização do insertion sort no seu melhor caso com o gráfico praticamente linear. Os picos se devem a variação de desempenho da máquina uma vez que o arranjo não possui repetição aumentando o número de interações.

`Cenário`: _Arranjo em ordem não crescente_

![insertion sort_non-ascending order](data/insertion/insertion%20sort_non-ascending%20order.png)

Visualização do pior caso, onde o algoritmo inverte completamente o vetor e sua complexidade é inevitavelmente quadrática.

`Cenário`:  _Arranjo 75% ordenado_

![insertion sort_sorted: 75%](data/insertion/insertion%20sort_sorted:%2075%25.png)

`Cenário`: _Arranjo 50% ordenado_

<img src="data/insertion/insertion%20sort_sorted:%2050%25.png" alt="insertion sort_sorted: 50%" style="zoom:150%;" />



`Cenário`: _Arranjo 25% ordenado_

<img src="data/insertion/insertion%20sort_sorted:%2025%25.png" alt="insertion sort_sorted: 25%" style="zoom:150%;" />



`Comparação`: _Arranjo parcialmente ordenado_ 

![comparação insertion 25,50,75](data/insertion/compara%C3%A7%C3%A3o%20insertion%2025,50,75.png)

O melhor cenário para o insertion é um arranjo com ordem parcial tendendo a ordem total. Fica clara a redução e/ou inexistência de picos no tempo de execução quanto mais ordenado estiver o vetor.





### Selection Sort

* Ordenação por seleção: seleciona o menor item e colocar na primeira posição, seleciona o segundo menor item e colocar na segunda posição, segue estes passos até que reste um único elemento. 

* Complexidade em todos os casos: $O(n²)$ 

* Não é estável.

* Funcionamento:

  ```
   var i,j,aux,menor : INTEIRO
   PARA i=0 ATE (vet.tamanho-1) PASSO 1
    menor = i
    PARA j=i+1 ATE vet.tamanho PASSO 1
     SE (vet[menor] > vet[j]) ENTAO
      menor = j
      FIMSE
      FIMPARA
     SE (menor != i) ENTAO
      aux = vet[menor]
      vet[menor] = vet[i]
      vet[i] = aux
    FIMSE
   FIMPARA
  ```



`Cenário`: _Arranjo completamente aleatório_ 

![selection sort_Full random](data/selection/selection%20sort_Full%20random.png)



`Cenário`: _Arranjo em ordem não decrescente_

![selection sort_non-descending order](data/selection/selection%20sort_non-descending%20order.png)



`Cenário`: _Arranjo em ordem não crescente_ 

![selection sort_non-ascending order](data/selection/selection%20sort_non-ascending%20order.png)



`Cenário`: _Arranjo 75% ordenado_ 

![selection sort_sorted: 75%](data/selection/selection%20sort_sorted:%2075%25.png)



![selection sort_sorted: 50%](data/selection/selection%20sort_sorted:%2050%25.png)

![selection sort_sorted: 25%](data/selection/selection%20sort_sorted:%2025%25.png)



![comparação selection s5,50,75](data/selection/compara%C3%A7%C3%A3o%20selection%20s5,50,75.png)

O selection sort tem como única vantagem a sua implementação simples. Todos os gráficos possuem praticamente o mesmo tempo de execução nos 6 cenários apresentados, isso se deve ao fato de que antes de fazer qualquer troca, o algoritmo realiza uma busca sequencial( $O(n-i)$ ) para cada posição do vetor, tornando-o ineficiente.





### Bubble Sort



