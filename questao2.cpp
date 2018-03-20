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


void insertSJF(std::vector< Process >& vector, Process& newProcess){
	int internalT = 0; // indica o tempo que o escalonador vai olhar novamente para os processos em busca do melhor
	for(std::vector< Process >::iterator el = vector.begin(); el != vector.end(); ++el){
		if(el->delay > internalT){
			internalT = el->delay; 
		}
		/*
		 * se o delay do novo processo for menor que o tempo atual da cpu ou for menor que o delay do processo no vetor
		 * e obviamente ele tem que ser menor em tempo de execução que o processo no vetor
		 */
		if((el->delay >= newProcess.delay || internalT >= newProcess.delay) && el->execT > newProcess.execT){
			vector.insert(el, newProcess); //caso todas as condiçoes forem aceitas, inserir na frente do processo "el"
			return;
		}

		internalT += el->execT;
	}
	// se não houver nenhum, insira no fim
	vector.push_back(newProcess);
}

int main(){
	int counter; // numero de entradas inseridas pelo usuario
	int times = 1; // teste de numero "times"
	cin >> counter;

	while(counter != 0){
		vector<Process> processes; 

		while(counter--){
			// Recebe os dados dos processos pelo usuario e insere de forma ordenada no vetor
			Process process;
			cin >> process.delay >> process.execT;
			process.id = processes.size()+1;

			insertSJF(processes, process);
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
