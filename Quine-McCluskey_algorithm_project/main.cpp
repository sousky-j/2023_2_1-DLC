#define _CRT_SECURE_NO_WARNINGS
#include <iostream>//�⺻ ����� ���
#include <fstream>//���� ����� ���
#include <string>//��Ʈ�� ���
#include <vector>//���� ���
#include <utility>//��� ���
#include <algorithm>//�˰��� ���
using namespace std;
class group
{
public:
	vector<pair<string, bool>> minterm;
	int data;
	group() { this->data = 0; }
	~group() { minterm.clear(); }
};
bool read_data();//V ���� �ҷ����� �Լ�, ��ȯ������ ȣ�� ���� ���� �Ǵ�
int cnt_ones(string arr);//��Ʈ �ȿ� 1�� ������ ���� ��ȯ�ϴ� �Լ�
void set_term(pair<string, bool> new_data);//V �Է¹��� ���� tmp_list�� �ִ� �Լ�
bool isprimeterm(string a, string b);//V �� term�� ����ȭ ������ ������ �Ǻ��ϴ� �Լ� �Ǹ� true, �ȵǸ� false
pair<string, bool> make_minterm(string a, string b);//V ����ȭ�� ���� ������ִ� �Լ�
void check_overlap();//V ����ȭ ���� tmp�� ������ �� �ߺ��� Ȯ���ϰ� �����ϴ� �Լ�
void change_list();//V list�� tmp_list�� ��ȯ�ϴ� �Լ�
void elimination();//V ����ȭ�ϴ� �� ���� �Լ� 
bool check_condition();//V ����ȭ ������ ������ üũ�ϴ� �Լ�, ����ȭ�� �������� 1, �ƴϸ� 0
void PI_extraction();//��ǥ�� ���� PI�� PI ������ �����ϴ� �Լ�
void Petrick_Method();//epi�� �̾Ƴ��� �˰����� �����Ͽ� epi�� �����ϴ� �Լ�
bool iscovercorrect(string a, string b);//minterm�� �����ϴ� PI���� Ȯ���ϴ� �Լ�
void save_EPI();//���Ͽ� EPI�� �����ϴ� �Լ�

int n, n_1;//��Ʈ���� �Է¹��� ����, ��Ʈ��+1
group* list = NULL, * tmp_list = NULL;//���� ����Ʈ�� �����ϴ� ����, ���ο� column�� �� �� ���� �� �����ϴ� �ӽ� ����
vector<string> minterm, PI;//���Ͽ��� �ҷ��� minterm���� ���� �����ϴ� �迭 ����, �� �� ���� prime implicant�� ������ ����
vector<string> EPI;//EPI�� ��� ����

int main(void)
{
	if (read_data()) return 1;//���� ȣ�� ���н� ���α׷� ����
	while (1)
	{
		elimination();//����ȭ ���� �Լ� ȣ��
		check_overlap();//�ߺ� ���� �Լ� ȣ��
		PI_extraction();//list�� ���� �� PI�� ���� �Լ� ȣ��
		if (check_condition())	break;//���� ���� ���� �Լ�
		change_list();//list�� tmp_list ���� �Լ� ȣ��
	}
	delete[] list;//�Ҵ� ����
	delete[] tmp_list;//�Ҵ� ����
	Petrick_Method();//���� ��Ʈ�� ��Ʈ���� ��� �Լ� ȣ��
	save_EPI();//���Ͽ� EPI �����Լ� ȣ��
	return 0;
}

void elimination()
{
	for (int i = 1; i < n_1; i++)//�׷� �� ��ŭ
	{
		int size = static_cast<int> (list[i - 1].minterm.size());
		for (int j = 0; j < size; j++)//���� �׷�(���� �׷�)�� ������ ����ŭ
		{
			for (int k = 0; k < list[i].minterm.size(); k++)//�� �׷�(���� �׷�)�� ������ ����ŭ
			{
				if (isprimeterm(list[i - 1].minterm[j].first, list[i].minterm[k].first))//���� ����ȭ �������� üũ
				{
					set_term(make_minterm(list[i - 1].minterm[j].first, list[i].minterm[k].first));//����ȭ �� ���� �� tmp�� ����
					list[i - 1].minterm[j].second = true;//üũǥ��
					list[i].minterm[k].second = true;//üũǥ��
				}
			}
		}
	}
}
void PI_extraction()
{
	for (int i = 0; i < n_1; i++)//�׷캰��
	{
		for (int j = 0; j < list[i].minterm.size(); j++)//�� �׷� ��ȸ
		{
			if (list[i].minterm[j].second == false)//��ǥ�� �� üũ
				PI.push_back((list[i].minterm[j].first));//PI�� ����
		}
	}
}
bool isprimeterm(string a, string b)
{
	int len = static_cast<int>(a.length());//������ ���̴� �����Ƿ� �ϳ��� ���̸� �ҷ���
	int cnt = 0;//�ٸ� �ڸ��� �Ǻ��ϴ� ����
	for (int i = 0; i < len; i++)
	{
		if (cnt > 1)	return false;//2�� �̻� �ٸ��� false
		if (abs(a[i] - b[i]) == 1)	cnt++;// ���� 0,1�̸� cnt ����
		else if (abs(a[i] - b[i]) == 3 || abs(a[i] - b[i]) == 4)	return false;//�����°� ���ڰ� ���� false
	}
	return true;//���� �ϳ��� �ٸ��� true
}
pair<string, bool> make_minterm(string a, string b)
{
	pair<string, bool> new_term = make_pair(a, false);//�ϴ� �� �� �ϳ��� string���� ����
	int len = static_cast<int> (a.length());//�ϳ��� ���̸� �ҷ���
	for (int i = 0; i < len; i++)
	{
		if (a[i] != b[i])  new_term.first[i] = '-';//�ϳ��� �ٸ� �κ��� ���� ���������� ����
	}
	return new_term;//���� ���� ��ȯ
}
void set_term(pair<string, bool> new_data)
{
	if (tmp_list == NULL)//tmp_list�� �Ҵ�Ǿ����� ������ �׷� �迭�� �Ҵ���
	{
		tmp_list = new group[n_1];
		for (int i = 0; i < n_1; i++)
			tmp_list[i].data = i;
	}
	int cnt = cnt_ones(new_data.first);//�Է¹��� �������� 1�� ������ ��
	tmp_list[cnt].minterm.push_back(make_pair(new_data.first, new_data.second));//�ش� �׷쿡 ����
}
void check_overlap()
{
	if (tmp_list != NULL)//tmp���� ���� �߻� ���� ���
	{
		for (int i = 0; i < n_1; i++)//unique�� �̿��Ͽ� �ߺ��� vector�� �ڷ� �̵���Ŵ, ���� erase�� ����
			tmp_list[i].minterm.erase(unique(tmp_list[i].minterm.begin(), tmp_list[i].minterm.end()), tmp_list[i].minterm.end());
	}
}
bool check_condition()//����ȭ ������ ������ üũ�ϴ� �Լ�, ����ȭ�� �������� 1, �ƴϸ� 0
{
	for (int i = 0; i < n_1; i++)//�׷� �� ��ŭ
	{
		int size = static_cast<int> (list[i].minterm.size());
		for (int j = 0; j < size; j++)//�� �׷츶��
		{
			if (list[i].minterm[j].second == true)  return false;//üũ ǥ�ð� �ִٴ� ���� tmp �÷��� �ִٴ� ���̹Ƿ� false
		}
	}
	return true;//�ϳ��� üũ ǥ�ð� ���� ��� ���Ḧ ���� true ��ȯ
}
void Petrick_Method()
{
	int rows = PI.size();//table �� ����
	int cols = minterm.size();//table �� ����
	int** table = new int* [rows];//PI ������ŭ �� �Ҵ�
	for (int i = 0; i < rows; i++)//minterm ������ŭ �� �Ҵ�
		table[i] = new int[cols];
	for (int i = 0; i < rows; i++)//�� �ึ��
	{
		for (int j = 0; j < cols; j++)//�� ������
		{
			if (iscovercorrect(minterm[j], PI[i]))	table[i][j] = 1;//minterm�� �����ϴ� PI���� üũ�Ͽ� ������ 1
			else table[i][j] = 0; // �ƴϸ� 0 ��ȯ
		}
	}
	for (int i = 0; i < cols; i++)
	{
		int cnt = 0;//1 ���� �� ����
		for (int j = 0; j < rows; j++)
		{
			if (table[j][i] == 1)//1 ã���� cnt ����
				cnt++;
		}
		if (cnt == 1)//x�� 1�ⰳ��
		{
			for (int j = 0; j < rows; j++)//���� ���鼭 1�� ���� �ٽ� ã��
			{
				if (table[j][i] == 1)//1�� ���� ã��
				{
					EPI.push_back(PI[j]);//�׶��� PI�� EPI�� ä��, ����
					for (int k = 0; k < cols; k++)//�ٸ� ���� �ִ� �� ã��
					{
						if (table[j][k] == 1)//1�ΰ� ã��
						{
							for (int p = 0; p < rows; p++)//1�� ���� ���� �� 0���� ����
								table[p][k] = 0;
						}
					}
					break;
				}
			}
		}
	}
	vector<int> cover(rows);
	while(1)
	{
		int stop = 0;//loop stop�� ���� ���� ���� üũ
		for (int i = 0; i < rows; i++)//table�� ��� ĭ�� üũ�Ͽ� 1�� ĭ Ȯ��
		{
			for (int j = 0; j < cols; j++)
			{
				if (table[i][j] == 1)
					stop++;
			}
		}
		if (!stop) break;//1�� ĭ�� �ƹ����� ������ stop
		for (int i = 0; i < rows; i++)//�� �ึ��
		{
			int cnt = 0;
			for (int j = 0; j < cols; j++)//�� ������
			{
				if (table[i][j] == 1)//1�� ���� cnt ����
					cnt++;
			}
			cover.push_back(cnt);//cover vector�� PI�� �����ϴ� minterm ���� �� ����
		}
		int max_id = 0;//�ִ� �ε��� ����, ù���� �ε���(0)���� �ʱ�ȭ
		for (int i = 0; i < rows; i++)//cover vector ��ȸ
		{
			if (cover[max_id] < cover[i]) max_id = i;//�ִ� ���� ���� ����, �ִ� �ε��� ����
		}
		EPI.push_back(PI[max_id]);//�ִ� ���� Ŀ�� PI�� EPI�� ä��
		for (int i = 0; i < cols; i++)//PI �ش� ����
		{
			if (table[max_id][i] == 1)//1�� �κ��� 0���� �ٲ�
			{
				for (int j = 0; j < rows; j++)//�� ���� ��� 0���� �ٲ�(Ŀ���ϹǷ�)
					table[j][i] = 0;
			}
		}
	}
	for (int i = 0; i < rows; i++)//�޸� ����
		delete[] table[i];//�޸� ����
	delete[] table;//�޸� ����
}
bool iscovercorrect(string a, string b)
{
	int len = static_cast<int>(a.length());
	for (int i = 0; i < len; i++)
	{
		if (a[i] != b[i] && a[i] != '-' && b[i] != '-')//�����ϴ� ��찡 �ƴϹǷ� false ��ȯ
			return false;
	}
	return true;//�����ϴ� ����̹Ƿ� true ��ȯ
}
void change_list()
{
	delete[] list;//list �Ҵ� ����
	list = tmp_list;//tmp_list�� list�� �ѱ�
	tmp_list = NULL;//tmp�迭�� NULL�� ����
}
int cnt_ones(string arr)//��Ʈ �ȿ� 1�� ������ count�ϰ� ��ȯ�ϴ� �Լ�
{
	int cnt = 0;//�ε��� ����, 1�� ���� ����
	for (int i = 0; i < arr.length(); i++)
		if (arr[i] == '1')	cnt++; // 1�� �� cnt�� ������
	return cnt;
}
bool read_data()
{
	//////data define///////
	string line;
	char c;
	ifstream read_file;
	read_file.open("input_minterm.txt");//���� ����
	if (read_file.fail())	return 1;//���� ȣ�� ���н� 1 ��ȯ
	std::getline(read_file, line);//���� ù�� �޾ƿ�
	n = stoi(line);//���ڿ��� ���ڸ� int�� �ٲ�
	n_1 = n + 1;//n_1�� ���� ����
	list = new group[n_1];//��Ʈ�� +1 (0~n����)��ŭ �׷��� ����
	for (int i = 0; i < n_1; i++)//ó�� ����Ʈ�� 1 ���� �����͸� �� ����Ʈ �ε����� ����
		list[i].data = i;
	while (!read_file.eof())//////���Ͽ��� �׷쿡 �����ϴ� �κ�//////////
	{
		//���� m�� �����̽� �������� ������
		read_file.get(c);
		read_file.get(c);
		std::getline(read_file, line);//���� �޾ƿ�
		int tmp = cnt_ones(line);//1�� ������ ��
		list[tmp].minterm.push_back(make_pair(line, false));//1������ �׷����� ���� ������
		minterm.push_back(line);//minterm�� ������ ������
	}
	read_file.close();//���� �ݱ�
	return 0;
}
void save_EPI()
{
	ofstream write_file;//���� ��� Ŭ���� ����
	write_file.open("result.txt");//���� ����
	for (int i = 0; i < EPI.size(); i++)  write_file << EPI[i] << "\n";//���Ͽ� ���پ� EPI�� ���
	write_file.close();//���� �ݱ�
}