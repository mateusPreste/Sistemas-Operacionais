#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

typedef struct Process{
	int delay; // tempo de entrega
	int execT; // tempo de duração do processo
	int id; // numeração do processo de acordo com a entrada, iniciando do 1
} Process;

/*
 * Acho necessário uma função de inserção ordenada pois é possivel inserir um processo em qualquer ordem
 * E o FIFO vai executar o primeiro processo disponivel, que pode não ser o primeiro inserido pelo usuario, devido ao tempo de entrega
 * Insere o par de inteiros de forma ordenada, do menor para o maior "tempo de entrega"
 */
void insertFCFS(std::vector< Process >& vector, Process& element){
	for(std::vector< Process >::iterator it = vector.begin(); it != vector.end(); ++it){
		//Se encontrar um elemento no vetor que tem "tempo de entrega" maior, insira antes dele
		if(it->delay > element.delay){
			/*
			 * insere em uma posição anterior que onde o iterador está
			 * não é possivel inserir na ultima posição do vetor desta forma
			 */
			vector.insert(it, element); 
			return;
		}
	}
	// se não houver nenhum, insira no fim
	vector.push_back(element);
}

int main(){
	int counter; // numero de entradas inseridas pelo usuario
	int times = 1; // teste de numero "times"
	cin >> counter;

	while(counter != 0){
		vector< Process > processes;
		
		while(counter--){
			Process process;
			cin >> process.delay >> process.execT;
			process.id = processes.size()+1;

			insertFCFS(processes, process);
		}

		int cpuT = 0; // indica o tempo da cpu
		int processT = 0; //indica o tempo de cpu quando o processo atual será executado
		int delay = 0; // indica o tempo de ingresso do processo

		double execT = 0; // o tempo de execução de todos os processos
		double waitT = 0; // o tempo de espera de espera de todos os processos

		string sequence = ""; // string com a sequencia da execução dos processos, P1 P2 P3 ...

		vector< Process >::iterator it = processes.begin();
		for(it; it != processes.end(); it++)
		{
			cpuT = processT; // o tempo de cpu atual é igual o tempo 
			sequence += "P"+to_string(it->id)+" "; 

			delay = it->delay;
			int time = it->execT;

			if(delay > cpuT){ // se o tempo de ingresso for maior que o tempo atual de cpu
				cpuT = delay; // vamos até lá logo
			}

			// atualiza com o novo processo
			processT = cpuT+time; 
			execT += processT-delay; 
			waitT += cpuT-delay;
		}
		cout << "Teste " << times++ << endl;
		cout << "Tempo medio de execucao: " << fixed << std::setprecision(5) << (execT*1.0)/processes.size() << "s" << endl;
		cout << "Tempo medio de espera " << (waitT)/processes.size() << "s" << endl;
		cout << sequence << endl;

		cin >> counter;
	}
}
