[![Open in Visual Studio Code](https://classroom.github.com/assets/open-in-vscode-c66648af7eb3fe8bc4f294546bfd86ef473780cde1dea487d3c4ff354943c9ae.svg)](https://classroom.github.com/online_ide?assignment_repo_id=8906371&assignment_repo_type=AssignmentRepo)



# BlockChain Project 
__CS2023 - Algoritmos y Estructuras de datos__

### Integrantes:
- Gabriel Enrique Espinoza Hernández
- Kevin Abraham Huaman Vega
- Paolo Vásquez Grahammer 

_Profesor a cargo_: Heider Sanchez


## Fundamento del proyecto
El proyecto consiste en desarrollar una aplicación transaccional de interacción de datos teniendo
como base de seguridad una estructura de datos de cadena de bloques (Blockchains en un solo
host). 

### Caso de estudio
Se implementó una blockchain similar a la de Bitcoin para hacer transacciones monetarias, buscando la securidad y confidencialidad de las transacciones realizadas, pero a su vez dando la posibilidad de alterarlas.

### Importancia del Blockchain en el dominio de datos elegido
La blochain toma relevancia en la seguridad de los datos de las transacciones. Si bien son públicas, se necesita aplicar cierta fuerza para poder obtener generar nuevas transacciones, y más fuerza para modificarlas. Esto beneficia en que, mientras más robusta sea la blockhain, mayor será la fuerza necesaria para modificar los datos contenidos en ella, lo que desinsentiva el hacerlo. 

### Explicación de la estructura de datos del Blockchain y la estrategia para asegurar la integridad de su contenido. Además, indicar cómo se implementó el proof of work.
Dado que cada bloque hace referencia a al bloque anterior en el campo llamado "Prev" o bloque padre, se optó por estructurar la blockhain en forma de __Forward List__, de tal manera que se cumpla la particularidad requerida, siendo cada bloque de la blockhain un nodo de la estructura.
 
Para asegurar la integridad de los datos, se aplicó el algoritmo SHA256 sobre la concatenación de los datos que conforman el bloque, los cuales contienen la fecha, el emisor, el receptor y el monto. El proof of work se aplicó al forzar que el hashcode generado para que un bloque sea aceptado empiece con 4 ceros consecutivos, de modo que de no hacerlo se reace el hashcode. Al crear y modificar un bloque, debe aplicarse lo anteriormente mencionado. Además, al modificar la información de un bloque, el hashcode de todos los bloques que le secundan deben volverse a calcular. Por último, el utilizar un foward list para representar la blockain, de querer acceder o modificar la información de los bloques más lejanos, se debe hacer un recorrido a lo largo de la estructura, de modo que tardará más en función a su posición.

### Bibliografía

Dev Tech Guy. Cryptocurrency (Bitcoin, Ethereum, Ripple) Blockchain in 30 minutes in C++! (Part 1). Extraído de: https://youtu.be/2VDQeQfh4Hs. Recuperado el 03/10/2022.

Porat, A; Pratap, A; Shah, P; Adkar, V. Blockchain Consensus: An analysis of
Proof-of-Work and its applications. Stanford University. Extraído de: https://www.scs.stanford.edu/17au-cs244b/labs/projects/porat_pratap_shah_adkar.pdf. Recopilado el 03/10/22 

Java T Point. (s/f.). Blockchain Proof of work. Extraído de: https://www.javatpoint.com/blockchain-proof-of-work#:~:text=Proof%20of%20work%20can%20be%20implemented%20in%20a%20blockchain%20by,for%20making%20the%20block%20valid. Recuperado el 03/10/22.

OpenSSL. (s/f.). Cripto. Extraído de: https://www.openssl.org/docs/man3.0/man7/crypto.html. Recopilado el 03/10/22.

Arora, S. (Septiembre, 22). What Is Bitcoin Mining: How Does it Work, Proof of Work, Mining Hardware and More. SimpliLearn. Extraído de: https://www.simplilearn.com/bitcoin-mining-explained-article. Recuperado el 04/10/22.
