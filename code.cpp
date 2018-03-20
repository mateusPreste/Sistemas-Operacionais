#include <iostream>
#include <vector>
using namespace std;

/*
	* Acho necessário uma função de inserção ordenada pois é possivel inserir um processo em qualquer ordem
	* E o FIFO vai executar o primeiro processo disponivel, que pode não ser o primeiro inserido pelo usuario, devido ao tempo de entrega
	* Insere o par de inteiros de forma ordenada, do menor para o maior "tempo de entrega"
*/
void insert(std::vector<std::vector<int>>& vector, std::vector<int>& element){
	for(std::vector<std::vector<int>>::iterator it = vector.begin(); it != vector.end(); ++it){
		//Se encontrar um elemento no vetor que tem "tempo de entrega" maior, insira antes dele
		if(it->at(0) > element.at(0)){
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
	cin >> counter;
	vector<vector<int>> processes;
	
	while(counter--){
		vector<int> process;
		int delay; // tempo de entrega
		int time; // tempo de duração do processo
		cin >> delay >> time;
		process.push_back(delay);
		process.push_back(time);
		process.push_back(processes.size()+1);

		insert(processes, process);
	}

	double total = 0;
	double last = 0;
	double waiting = 0;
	vector< vector<int> >::iterator it = processes.begin();
	for(it; it != processes.end(); it++)
	{
		cout << "P" << it->at(2) << endl;
		int delay = it->at(0);
		int time = it->at(1);
		if(total >= delay){
			last += time;
			total += last-delay;
			waiting += last-time-delay;
		} else{
			//TODO
			//se começar com delay maior que zero dá problema
			total += (delay-total)+time+total;
		}
	}
	cout << "tempo medio " << (total*1.0)/processes.size() << endl;
	cout << "tempo esperando " << (waiting)/processes.size();
}
