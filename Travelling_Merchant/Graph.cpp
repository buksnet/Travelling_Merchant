#include "graph.h"
#include <iomanip>


void graph::addvertex(const string& name)
{
    vmap::iterator itr = work.find(name);
    if (itr == work.end())
    {
        vertex* v;
        v = new vertex(name);
        work[name] = v;
        vertexes.push_back(name);
        return;
    }
    cout << "\nVertex already exists!"; 
}

void graph::addedge(const string& from, const string& to, const double& cost)
{
    vertex* f = (work.find(from)->second);
    vertex* t = (work.find(to)->second);
    pair<int, vertex*> edge = make_pair(cost, t);
    f->adj.push_back(edge);
}

void graph::initmatrix()
{
    cout <<  "adjacency matrix:" << endl;
    datamatrix.resize(work.size());
    for (int i = 0; i < work.size(); i++) {
        datamatrix[i].resize(work.size());
    }
    list<string>::iterator it = vertexes.begin();
    empty_space();
    for (int i = 0; i < work.size(); i++) {
        for (int j = 0; j < work.size(); j++) {
            datamatrix[i][j] = work[(*it)]->adj[j].first;
        }
        if (work.find(*it) != work.cend()) cout << " | " << setw(5) << "'" + work[(*it)]->name + "'";
        it++;
    }
    cout << endl; underscore(work.size()); cout << endl;
    it = vertexes.begin();
    for (int i = 0; i < work.size(); i++) {
        cout << setw(5) << "'" + work[(*it)]->name + "' | ";
        it++;
        for (int j = 0; j < work.size()-1; j++) {
			if (datamatrix[i][j] != INT32_MAX)
			cout << setw(5) << left << datamatrix[i][j] << " | ";
			else cout << setw(5) << left << "inf" << " | ";
        }
		if (datamatrix[i][work.size() - 1] != INT32_MAX)
        cout << setw(5) << left << datamatrix[i][work.size() - 1] << endl;
		else cout << setw(5) << left << "inf" << endl;
	}
}

void graph::connectAll(const string & name) {
    for (list<string>::iterator it = vertexes.begin(); it != vertexes.end(); ++it) {
        if (name != work[(*it)]->name) {
            int cost;
            cout << "Input " << name << " -> " << work[(*it)]->name << " cost: " << endl;
            cin >> cost;
            addedge(name, work[(*it)]->name, cost);
            addedge(work[(*it)]->name, name, cost);
        }
        else {
            addedge(name, work[(*it)]->name, INT32_MAX);
        }
    }
}


void graph::removeedge(const string& name) {
    for (list<string>::iterator it = vertexes.begin(); it != vertexes.end();) {
        if (work[(*it)]->name == name) {
            work.erase(*it);
        }
        else {
            ++it;
        }
    }
}


int graph::min(vector<int> pile) {
    int mini = 100000000;
    for (int const& i : pile) {
		if (i < mini && i != INT32_MAX) mini = i;
    }
    return mini;
}


void graph::underscore(int q)
{
    for (int i = 0; i < q; i++) {
        cout << "________";
    }
	cout << "____" << endl;
}

void graph::empty_space() {
    int max = 0;
    for (auto const& it : work) {
        if (it.second->name.size() > max) max = it.second->name.size();
    }
    cout << setw(max+2) << " ";
}


using namespace std;
LittleAlgorithm::LittleAlgorithm() {}
LittleAlgorithm::LittleAlgorithm(vector<vector<int>> Data) { LoadData(Data); }
LittleAlgorithm::LittleAlgorithm(char* Path) { LoadData(Path); }
vector<pair<int, int>> LittleAlgorithm::run()
{
	if (!validateData()) throw "Not valid data.";
	matrixProcedure(vector<vector<int>>(data));
	return export_result;
}

int LittleAlgorithm::getMin(vector<vector<int>> matrix, int sel, check pos)
{
	int min = INT32_MAX;
	for (int i = 0; i < matrix[sel].size() - 1; i++)
		switch (pos)
		{
		case LittleAlgorithm::Row:
			if (min > matrix[sel][i])
				min = matrix[sel][i];
			break;
		case LittleAlgorithm::Col:
			if (min > matrix[i][sel])
				min = matrix[i][sel];
			break;
		}
	return min;
}
void LittleAlgorithm::matrixProcedure(vector<vector<int>> matrix)
{
	if (block) return;
	//Определяем точку возврата и удаляем необходимое ребро
	if (matrix.size() - 1 > 2) {
		vector<int> vertexes;
		for (int i = 0; i < result.size(); i++) {
			vertexes.push_back(result[i].first);
			vertexes.push_back(result[i].second);
		}
		for (int i = 0; i < vertexes.size(); i++) {
			pair<int, int> elem(INT32_MAX, INT32_MAX), elem1(INT32_MAX, INT32_MAX);
			for (int j = 0; j < vertexes.size(); j++) {
				if (vertexes[i] != vertexes[j]) {
					for (int k = 0; k < matrix[matrix.size() - 1].size() - 1; k++) {
						if (vertexes[i] == matrix[k][matrix[k].size() - 1]) elem.first = k;
						if (vertexes[j] == matrix[k][matrix[k].size() - 1]) elem1.first = k;
					}
					for (int k = 0; k < matrix.size() - 1; k++) {
						if (vertexes[i] == matrix[matrix.size() - 1][k]) elem.second = k;
						if (vertexes[j] == matrix[matrix.size() - 1][k]) elem1.second = k;
					}
				}
			}
			for (int i = 0; i < matrix.size() - 1; i++)
				for (int j = 0; j < matrix.size() - 1; j++)
					if (i == elem1.first && j == elem1.second)
						matrix[elem1.first][elem1.second] = INT32_MAX;
			for (int i = 0; i < matrix.size() - 1; i++)
				for (int j = 0; j < matrix.size() - 1; j++)
					if (i == elem.first && j == elem.second)
						matrix[elem.first][elem.second] = INT32_MAX;
		}
	}

	//Вычитаем из каждой строки минимальное значение
	for (int i = 0; i < matrix.size() - 1; i++) {
		int min = 0;
		if ((min = getMin(matrix, i, check::Row)) == INT32_MAX) {
			showMatrix(matrix);
			cout << endl << "Bad road" << endl;
			return;
		}
		if ((min = getMin(matrix, i, check::Row)) != 0)
			for (int j = 0; j < matrix[i].size() - 1; j++)
				if (matrix[i][j] != INT32_MAX) matrix[i][j] -= min;
	}

	//Вычитаем из каждого столбца минимальное значение
	for (int i = 0; i < matrix[matrix.size() - 1].size() - 1; i++) {
		int min = 0;
		if ((min = getMin(matrix, i, check::Col)) == INT32_MAX) {
			showMatrix(matrix);
			std::cout << endl << "Bad road" << endl;
			return;
		}
		if ((min = getMin(matrix, i, check::Col)) != 0)
			for (int j = 0; j < matrix.size() - 1; j++)
				if (matrix[j][i] != INT32_MAX) matrix[j][i] -= min;
	}

	//Находим максимально оцененный ноль
	int Max = 0;
	for (int i = 0; i < matrix.size() - 1; i++)
		for (int j = 0; j < matrix[i].size() - 1; j++)
			if (matrix[i][j] == 0) {
				matrix[i][j] = INT32_MAX;
				int max = (getMin(matrix, i, check::Row) == INT32_MAX || getMin(matrix, j, check::Col) == INT32_MAX) ? INT32_MAX : getMin(matrix, i, check::Row) + getMin(matrix, j, check::Col);
				if (max > Max) Max = max;
				matrix[i][j] = 0;
			}

	//Находим все нули максимальная оценка которых равна Max
	vector<pair<int, int>> Maxs;
	for (int i = 0; i < matrix.size() - 1; i++)
		for (int j = 0; j < matrix[i].size() - 1; j++)
			if (matrix[i][j] == 0) {
				matrix[i][j] = INT32_MAX;
				int max = (getMin(matrix, i, check::Row) == INT32_MAX || getMin(matrix, j, check::Col) == INT32_MAX) ? INT32_MAX : getMin(matrix, i, check::Row) + getMin(matrix, j, check::Col);
				if (max == Max) Maxs.push_back(pair<int, int>(matrix[i][matrix.size() - 1], matrix[matrix.size() - 1][j]));
				matrix[i][j] = 0;
			}
	//Debug: Вывод координат выбранных нулей
	//std::cout << "Maxs - ";
	//for (int i = 0; i < Maxs.size(); i++)
		//std::cout << Maxs[i].first << " " << Maxs[i].second << "\t";
	//std::cout << endl;
	//Вывод матрицы
	showMatrix(matrix);
	//Завершаем выполнение данной ветви если нету нулей
	if (Maxs.size() == 0) {
		std::cout << "Bad road." << endl;
		return;
	}

	for (int i = 0; i < Maxs.size(); i++) {
		//Добавляем вершину в массив с результатом
		result.push_back(Maxs[i]);
		//Если размер матрицы порядка 1, выводим результат и завершаем текущию ветвь
		if (matrix.size() - 1 == 1) {
			for (int i = 0; i < result.size(); i++)
				std::cout << "(" << result[i].first << ", " << result[i].second << ")\t";
			std::cout << endl;
			if (export_result.empty()) {
				export_result = result;
				block = true;
			}
			result.pop_back();
			return;
		}
		//Создаем копию текущей матрицы и удаляем из нее строку и столбец выбранного нуля
		vector<vector<int>>  temp(matrix);
		pair<int, int> elem(INT32_MAX, INT32_MAX), elem1(INT32_MAX, INT32_MAX);
		for (int j = 0; j < temp[temp.size() - 1].size() - 1; j++) {
			if (Maxs[i].first == temp[j][temp[j].size() - 1]) elem.first = j;
			if (Maxs[i].second == temp[j][temp[j].size() - 1]) elem1.first = j;
		}
		for (int j = 0; j < temp.size() - 1; j++) {
			if (Maxs[i].second == temp[temp.size() - 1][j]) elem.second = j;
			if (Maxs[i].first == temp[temp.size() - 1][j]) elem1.second = j;
		}

		for (int i = 0; i < temp.size() - 1; i++)
			for (int j = 0; j < temp.size() - 1; j++)
				if (i == elem1.first && j == elem1.second)
					temp[elem1.first][elem1.second] = INT32_MAX;

		for (int j = 0; j < temp[temp.size() - 1].size(); j++)
			temp[j].erase(temp[j].begin() + elem.second);
		temp.erase(temp.begin() + elem.first);
		//Вызываем рекурсивно эту же функцию для уже новой матрицы
		matrixProcedure(temp);
		//Удаляем последние значение из массива с результатом 
		result.pop_back();
	}
}
//Вывод матрицы
void LittleAlgorithm::showMatrix(vector<vector<int>> temp)
{
	std::cout << endl;
	std::cout << "\t";
	for (int i = 0; i < temp[temp.size() - 1].size() - 1; i++) {
		std::cout << temp[temp.size() - 1][i] << "\t";
	}
	std::cout << endl;
	for (int i = 0; i < temp[0].size()+1; i++)
		for (int j = 0; j < 6; j++) std::cout << "_";
	std::cout << endl << endl;
	for (int i = 0; i < temp.size() - 1; i++) {
		std::cout << temp[i][temp.size() - 1] << " | " << "\t";
		for (int j = 0; j < temp[i].size() - 1; j++)
			if (temp[i][j] != INT32_MAX && j != temp.size() - 1)std::cout << temp[i][j] << "\t";
			else std::cout << "inf" << "\t";
		std::cout << endl;
	}
	std::cout << endl;
}
int LittleAlgorithm::getResultSum()
{
	int sum = 0;
	for (int i = 0; i < result.size(); i++)
		sum += data[result[i].first - 1][result[i].second - 1];
	return sum;
}
bool LittleAlgorithm::validateData()
{
	for (int i = 0; i < data.size(); i++)
		for (int j = 0; j < data[i].size(); j++)
			if (data[i][j] == 0)
				data[i][j] = INT32_MAX;

	vector<vector<int>> temp(data);
	for (int i = 0; i < data.size(); i++)
		data[i].push_back(i + 1);
	vector<int> numeration;
	for (int i = 0; i < data[0].size(); i++)
		numeration.push_back(i + 1);
	data.push_back(numeration);

	return true;
}

bool LittleAlgorithm::LoadData(char* Path)
{
	ifstream file(Path, ios_base::in);
	if (!file.is_open()) throw "Can't open data file";
	int rows = GetStrCount(file), cols = GetColCount(file);
	for (int i = 0; i < rows; i++)
	{
		vector<int> temp;
		for (int j = 0; j < cols; j++)
		{
			int n;
			file >> n;
			temp.push_back(n);
		}
		data.push_back(vector<int>(temp));
	}
	file.seekg(0);
	return true;
}


bool LittleAlgorithm::LoadData(vector<vector<int>> Data)
{
	data = Data;
	return true;
}

int LittleAlgorithm::GetStrCount(ifstream& file)
{
	int count = 0;
	while (!file.eof()) {
		file.getline(new char[255], 255);
		count++;
	};
	file.seekg(0);
	return count;
}

int LittleAlgorithm::GetColCount(ifstream& file)
{
	int count = 0;
	char str[255];
	file.getline(str, 255);
	for (int i = 0; i < strlen(str); i++)
	{
		if (isdigit(str[i]))
			if (i != 0 && !isdigit(str[i - 1]))
				count++;
			else if (i == 0)
				count++;
	}
	file.seekg(0);
	return count;
}
