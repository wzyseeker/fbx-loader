#include"fbxģ�ͼ���-��̬ģ��.h"
#include"��������.h"

C��̬����::C��̬����(ComPtr<ID3D12Device> �豸, ComPtr<ID3D12GraphicsCommandList> �������, C�������ѹ���* �������ѹ���, C������Դ* ������Դ)
{
    this->�豸 = �豸;
    this->������� = �������;
    this->�������ѹ��� = �������ѹ���;
    this->������Դ = ������Դ;
}

//�����ļ�mds�ļ�-----------------------------------
void C��̬����::����mds�ļ�(wstring �ļ�����)
{
    ofstream ����ļ�;
    string �ļ�����;
    wstring ͼƬ����;
    WCHAR �ļ�����·��[128]{};
    wstring �ļ�����2;
    char ͼƬ����2[128]{};
    wstring ͼƬ����3;
    UINT �ַ������� = 0;
    int i = 0;
    int j = 0;

    wcscpy_s(�ļ�����·��, �ļ�����.c_str());
    for (int i = 0; i < wcslen(�ļ�����·��); i++)
    {
        if (�ļ�����·��[i] == '.')
        {
            �ļ�����·��[i] = '\0';
            break;
        }
    }

    if (CreateDirectory(�ļ�����·��, 0) == 0)
    {
        wstring bug = L"�ļ����� line:" + to_wstring(__LINE__) + L'\n';
        OutputDebugString(bug.c_str());
    }

    �ļ�����2 = �ļ�����·��;
    �ļ����� = �ļ�����2 + L"\\" + �ļ�����;

    ����ļ�.open(�ļ�����);

    if (!����ļ�.is_open())
    {
        wstring bug = L"�ļ��޷��� line:" + to_wstring(__LINE__) + L'\n';
        OutputDebugString(bug.c_str());
        PostQuitMessage(0);
        return;
    }

    �ļ����� = "����������" + to_string(����->Ԫ��.size()) + "��\n";
    ����ļ�.write(�ļ�����.c_str(), �ļ�����.size());

    for (i = 0; i < s��������->·����.size(); i++)
    {
        ͼƬ����.clear();
        j = 0;
        while (1)
        {
            if (s��������->·����[i][j] != '\0')
            {
                if (s��������->·����[i][j] == '/' || s��������->·����[i][j] == '\\')
                {
                    ͼƬ����.clear();
                    j++;
                }
                ͼƬ���� += s��������->·����[i][j];
                j++;
            }
            else
            {
                break;
            }
        }

        WideCharToMultiByte(CP_ACP, 0, ͼƬ����.c_str(), ͼƬ����.size(), ͼƬ����2, 128, 0, 0);

        ͼƬ����3 = ͼƬ����;
        ͼƬ���� = �ļ�����·��;
        ͼƬ���� += L'\\';
        ͼƬ���� += ͼƬ����3;

        CopyFile(s��������->·����[i].c_str(), ͼƬ����.c_str(), TRUE);

        �ļ����� = "�������ƣ�";
        �ļ����� += ͼƬ����2;
        �ļ����� += "��\n";
        ����ļ�.write(�ļ�����.c_str(), �ļ�����.size());
    }

    �ļ����� = "\n";
    ����ļ�.write(�ļ�����.c_str(), �ļ�����.size());

    for (i = 0; i < ����->Ԫ��.size(); i++)
    {
        char ����[128];
        int ���� = WideCharToMultiByte(CP_ACP, 0, ����->Ԫ��[i]->��������.c_str(), ����->Ԫ��[i]->��������.size(), ����, 128, 0, 0);
        ����[����] = '\0';
        string �������� = ����;

        �ļ����� = "��������.�������ƣ�" + �������� + "��\n"; to_string(1);
        ����ļ�.write(�ļ�����.c_str(), �ļ�����.size());

        �ļ����� = "��������.��ʼ������" + to_string(����->Ԫ��[i]->��ʼ����) + "��\n";
        ����ļ�.write(�ļ�����.c_str(), �ļ�����.size());

        �ļ����� = "��������.����������" + to_string(����->Ԫ��[i]->��������) + "��\n";
        ����ļ�.write(�ļ�����.c_str(), �ļ�����.size());

        �ļ����� = "��������.�任����" + to_string(����->Ԫ��[i]->�任.r[0].m128_f32[0]) + "��" +
            to_string(����->Ԫ��[i]->�任.r[0].m128_f32[1]) + "��" + to_string(����->Ԫ��[i]->�任.r[0].m128_f32[2]) + "��" +
            to_string(����->Ԫ��[i]->�任.r[0].m128_f32[3]) + "��" + to_string(����->Ԫ��[i]->�任.r[1].m128_f32[0]) + "��" +
            to_string(����->Ԫ��[i]->�任.r[1].m128_f32[1]) + "��" + to_string(����->Ԫ��[i]->�任.r[1].m128_f32[2]) + "��" +
            to_string(����->Ԫ��[i]->�任.r[1].m128_f32[3]) + "��" + to_string(����->Ԫ��[i]->�任.r[2].m128_f32[0]) + "��" +
            to_string(����->Ԫ��[i]->�任.r[2].m128_f32[1]) + "��" + to_string(����->Ԫ��[i]->�任.r[2].m128_f32[2]) + "��" +
            to_string(����->Ԫ��[i]->�任.r[2].m128_f32[3]) + "��" + to_string(����->Ԫ��[i]->�任.r[3].m128_f32[0]) + "��" +
            to_string(����->Ԫ��[i]->�任.r[3].m128_f32[1]) + "��" + to_string(����->Ԫ��[i]->�任.r[3].m128_f32[2]) + "��" +
            to_string(����->Ԫ��[i]->�任.r[3].m128_f32[3]) + "��\n";
        ����ļ�.write(�ļ�����.c_str(), �ļ�����.size());

        �ļ����� = "��������.����������" + to_string(����->Ԫ��[i]->��������) + "��\n";
        ����ļ�.write(�ļ�����.c_str(), �ļ�����.size());

        �ļ����� = "��������.����ͼ������" + to_string(����->Ԫ��[i]->����ͼ����) + "��\n";
        ����ļ�.write(�ļ�����.c_str(), �ļ�����.size());

        �ļ����� = "��������.����.�����䣺" + to_string(����->Ԫ��[i]->����.������.x) + "��" + 
            to_string(����->Ԫ��[i]->����.������.y) + "��" + to_string(����->Ԫ��[i]->����.������.z) + "��" + 
            to_string(����->Ԫ��[i]->����.������.w) + "��\n";
        ����ļ�.write(�ļ�����.c_str(), �ļ�����.size());

        �ļ����� = "��������.����.�Է��⣺" + to_string(����->Ԫ��[i]->����.�Է���.x) + "��" +
            to_string(����->Ԫ��[i]->����.�Է���.y) + "��" + to_string(����->Ԫ��[i]->����.�Է���.z) + "��" +
            to_string(����->Ԫ��[i]->����.�Է���.w) + "��\n";
        ����ļ�.write(�ļ�����.c_str(), �ļ�����.size());

        �ļ����� = "��������.����.�����⣺" + to_string(����->Ԫ��[i]->����.������.x) + "��" +
            to_string(����->Ԫ��[i]->����.������.y) + "��" + to_string(����->Ԫ��[i]->����.������.z) + "��" +
            to_string(����->Ԫ��[i]->����.������.w) + "��\n";
        ����ļ�.write(�ļ�����.c_str(), �ļ�����.size());

        �ļ����� = "��������.����.����ȣ�" + to_string(����->Ԫ��[i]->����.�����) + "��\n";
        ����ļ�.write(�ļ�����.c_str(), �ļ�����.size());

        �ļ����� = "��������.����.�߹⼶��" + to_string(����->Ԫ��[i]->����.�߹⼶��) + "��\n";
        ����ļ�.write(�ļ�����.c_str(), �ļ�����.size());

        �ļ����� = "��������.����.��͸���ȣ�" + to_string(����->Ԫ��[i]->����.��͸����) + "��\n";
        ����ļ�.write(�ļ�����.c_str(), �ļ�����.size());

        �ļ����� = "��������.��Χ��.���ģ�" + to_string(����->Ԫ��[i]->��Χ��.Center.x) + "��" + to_string(����->Ԫ��[i]->��Χ��.Center.y) + "��"
            + to_string(����->Ԫ��[i]->��Χ��.Center.z) + "��\n";
        ����ļ�.write(�ļ�����.c_str(), �ļ�����.size());

        �ļ����� = "��������.��Χ��.�뾶��" + to_string(����->Ԫ��[i]->��Χ��.Radius) + "��\n";
        ����ļ�.write(�ļ�����.c_str(), �ļ�����.size());

        �ļ����� = "��������.��Χ���.��Χ��������" + to_string(s��������->��Χ���[i].size()) + "��\n";
        ����ļ�.write(�ļ�����.c_str(), �ļ�����.size());

        for (int j = 0; j < s��������->��Χ���[i].size(); j++)
        {
            �ļ����� = "��Χ���.����ǰλ�ã�" + to_string(s��������->��Χ���[i][j].����ǰλ��.x) + "��" + to_string(s��������->��Χ���[i][j].����ǰλ��.y)
                + "��" + to_string(s��������->��Χ���[i][j].����ǰλ��.z) + "��\n";
            ����ļ�.write(�ļ�����.c_str(), �ļ�����.size());

            �ļ����� = "��Χ���.�߳���" + to_string(s��������->��Χ���[i][j].�߳�.x) + "��" + to_string(s��������->��Χ���[i][j].�߳�.y)
                + "��" + to_string(s��������->��Χ���[i][j].�߳�.z) + "��\n";
            ����ļ�.write(�ļ�����.c_str(), �ļ�����.size());

            �ļ����� = "\n";
            ����ļ�.write(�ļ�����.c_str(), �ļ�����.size());
        }

        �ļ����� = "\n";
        ����ļ�.write(�ļ�����.c_str(), �ļ�����.size());
    }

    �ļ����� = "\n";
    ����ļ�.write(�ļ�����.c_str(), �ļ�����.size());

    �ļ����� = "���㲼�֣�" + to_string(���㲼��) + "��\n";
    ����ļ�.write(�ļ�����.c_str(), �ļ�����.size());

    �ļ����� = "���㵥Ԫ��С��" + to_string(���㵥Ԫ��С) + "��\n";
    ����ļ�.write(�ļ�����.c_str(), �ļ�����.size());

    �ļ����� = "����������" + to_string(s��������->���㼯.size()) + "��\n";
    ����ļ�.write(�ļ�����.c_str(), �ļ�����.size());

    �ļ����� = "\n";
    ����ļ�.write(�ļ�����.c_str(), �ļ�����.size());
    for (i = 0; i < s��������->���㼯.size(); i++)
    {
        s��������->���㼯[i].λ��;

        �ļ����� = "����.λ�ã�" + to_string(s��������->���㼯[i].λ��.x) + "��" +
            to_string(s��������->���㼯[i].λ��.y) + "��" + to_string(s��������->���㼯[i].λ��.z) + "��\n";
        ����ļ�.write(�ļ�����.c_str(), �ļ�����.size());

        �ļ����� = "����.��������" + to_string(s��������->���㼯[i].������.x) + "��" + 
            to_string(s��������->���㼯[i].������.y) + "��" + to_string(s��������->���㼯[i].������.z) + "��\n";
        ����ļ�.write(�ļ�����.c_str(), �ļ�����.size());

        �ļ����� = "����.����" + to_string(s��������->���㼯[i].��������.x) + "��" +
            to_string(s��������->���㼯[i].��������.y) + "��\n";
        ����ļ�.write(�ļ�����.c_str(), �ļ�����.size());

        �ļ����� = "\n";
        ����ļ�.write(�ļ�����.c_str(), �ļ�����.size());
    }

    �ļ����� = "\n";
    ����ļ�.write(�ļ�����.c_str(), �ļ�����.size());

    �ļ����� = "������ʽ��" + to_string(������ʽ) + "��\n";
    ����ļ�.write(�ļ�����.c_str(), �ļ�����.size());

    �ļ����� = "����������" + to_string(��������) + "��\n";
    ����ļ�.write(�ļ�����.c_str(), �ļ�����.size());

    if (������ʽ == DXGI_FORMAT_R16_UINT)
    {
        for (i = 0; i < s��������->s����.size(); i = i + 3)
        {
            �ļ����� = "������������" + to_string(s��������->s����[i]) + "��" + to_string(s��������->s����[i + 1]) + "��" +
                to_string(s��������->s����[i + 2]) + "��\n";
            ����ļ�.write(�ļ�����.c_str(), �ļ�����.size());
        }
    }
    else if (������ʽ == DXGI_FORMAT_R32_UINT)
    {
        for (i = 0; i < s��������->����.size(); i = i + 3)
        {
            �ļ����� = "������������" + to_string(s��������->����[i]) + "��" + to_string(s��������->����[i + 1]) + "��" +
                to_string(s��������->����[i + 2]) + "��\n";
            ����ļ�.write(�ļ�����.c_str(), �ļ�����.size());
        }
    }

    �ļ����� = "\n";
    ����ļ�.write(�ļ�����.c_str(), �ļ�����.size());

    ����ļ�.close();
}

//�����ļ�
void C��̬����::����mds�ļ�(wstring �ļ�����, wstring �������Ƽ�)
{
    ifstream �����ļ�;
    wstring �ؼ��� = L"";
    wstring ��ֵ[20];
    char ��ֵ2[128]{};
    char ����[256];
    WCHAR ����2[256];
    int ���� = 0;
    int i = 0;
    UINT ���Բ��� = 0;
    map<wstring, int> id;
    UINT �������� = 0;
    UINT ���㲽�� = 0;
    UINT �������� = 0;
    UINT �ַ������� = 0;
    string ����·�� = "";
    char ͼƬ����[128]{};
    WCHAR ͼƬ����w[128]{};
    WCHAR ����·��w[128]{};
    int ���� = 0;
    UINT ��Χ���� = 0;
    wstring �ļ�����;
    bool �Ƿ���¼ = 0;

    this->�������Ƽ� = �������Ƽ�;

    id.insert(pair<wstring, int>(L"��������", 0));
    id.insert(pair<wstring, int>(L"��������.��������", 1));
    id.insert(pair<wstring, int>(L"��������.��ʼ����", 2));
    id.insert(pair<wstring, int>(L"��������.��������", 3));
    id.insert(pair<wstring, int>(L"��������.�任����", 4));
    id.insert(pair<wstring, int>(L"��������.��������", 5));
    id.insert(pair<wstring, int>(L"��������.����ͼ����", 6));
    id.insert(pair<wstring, int>(L"��������.����.������", 7));
    id.insert(pair<wstring, int>(L"��������.����.�Է���", 8));
    id.insert(pair<wstring, int>(L"��������.����.������", 9));
    id.insert(pair<wstring, int>(L"��������.����.�����", 10));
    id.insert(pair<wstring, int>(L"��������.����.�߹⼶��", 11));
    id.insert(pair<wstring, int>(L"��������.����.��͸����", 12));
    id.insert(pair<wstring, int>(L"���㲼��", 13));
    id.insert(pair<wstring, int>(L"���㵥Ԫ��С", 14));
    id.insert(pair<wstring, int>(L"��������", 15));
    id.insert(pair<wstring, int>(L"����.λ��", 16));
    id.insert(pair<wstring, int>(L"����.������", 17));
    id.insert(pair<wstring, int>(L"����.����", 18));
    id.insert(pair<wstring, int>(L"������ʽ", 19));
    id.insert(pair<wstring, int>(L"��������", 20));
    id.insert(pair<wstring, int>(L"����������", 21));
    id.insert(pair<wstring, int>(L"��������", 22));
    id.insert(pair<wstring, int>(L"��������.��Χ��.����", 23));
    id.insert(pair<wstring, int>(L"��������.��Χ��.�뾶", 24));
    id.insert(pair<wstring, int>(L"��������.��Χ���.��Χ������", 25));
    id.insert(pair<wstring, int>(L"��Χ���.����ǰλ��", 26));
    id.insert(pair<wstring, int>(L"��Χ���.�߳�", 27));

    �����ļ�.open(�ļ�����);

    if (!�����ļ�.is_open())
    {
        wstring bug = L"�ļ��޷��� line:" + to_wstring(__LINE__) + L'\n';
        OutputDebugString(bug.c_str());
        PostQuitMessage(0);
        return;
    }

    s�������� = new S��������;

    while (!�����ļ�.eof())
    {
        �ؼ���.clear();
        for(i = 0; i < ����; i++)
            ��ֵ[i].clear();
        ���� = 0;

        �����ļ�.getline(����, 256);
        �ַ������� = MultiByteToWideChar(CP_ACP, 0, ����, strlen(����), ����2, 256);
        ����2[�ַ�������] = '\0';

        i = 0;
        while (1)
        {
            if (����2[i] == L'��')
            {
                i++;
                ���� = 1;
            }

            if (����2[i] == L'��')
            {
                i++;
                ����++;
            }

            if (����2[i] == L'\0') break;
            
            if (���� == 0)
                �ؼ��� += ����2[i];

            if (���� > 0)
                ��ֵ[���� - 1] += ����2[i];

            i++;
        }

        if(�ؼ���[0] != L'\0')
            switch (id[�ؼ���])
            {
            case 0:
                ���� = new C��������;
                ����->Ԫ��.resize(stoi(��ֵ[0]));
                for (int i = 0; i < ����->Ԫ��.size(); i++)
                {
                    ����->Ԫ��[i] = new C��������::S����;
                }
                s��������->��Χ���.resize(stoi(��ֵ[0]));
                ����->����.resize(1);
                ����->����[0] = ������Դ->����ͼ;
                ����->�����ϴ�.resize(1);
                ����->�����ϴ�[0] = nullptr;
                break;

            case 1:
                ����->Ԫ��[���Բ���]->�������� = ��ֵ[0];
                break;

            case 2:
                ����->Ԫ��[���Բ���]->��ʼ���� = stoi(��ֵ[0]);
                break;

            case 3:
                ����->Ԫ��[���Բ���]->�������� = stoi(��ֵ[0]);
                break;

            case 4:
                ����->Ԫ��[���Բ���]->�任.r[0].m128_f32[0] = stof(��ֵ[0]); ����->Ԫ��[���Բ���]->�任.r[0].m128_f32[1] = stof(��ֵ[1]);
                ����->Ԫ��[���Բ���]->�任.r[0].m128_f32[2] = stof(��ֵ[2]); ����->Ԫ��[���Բ���]->�任.r[0].m128_f32[3] = stof(��ֵ[3]);
                ����->Ԫ��[���Բ���]->�任.r[1].m128_f32[0] = stof(��ֵ[4]); ����->Ԫ��[���Բ���]->�任.r[1].m128_f32[1] = stof(��ֵ[5]);
                ����->Ԫ��[���Բ���]->�任.r[1].m128_f32[2] = stof(��ֵ[6]); ����->Ԫ��[���Բ���]->�任.r[1].m128_f32[3] = stof(��ֵ[7]);
                ����->Ԫ��[���Բ���]->�任.r[2].m128_f32[0] = stof(��ֵ[8]); ����->Ԫ��[���Բ���]->�任.r[2].m128_f32[1] = stof(��ֵ[9]);
                ����->Ԫ��[���Բ���]->�任.r[2].m128_f32[2] = stof(��ֵ[10]); ����->Ԫ��[���Բ���]->�任.r[2].m128_f32[3] = stof(��ֵ[11]);
                ����->Ԫ��[���Բ���]->�任.r[3].m128_f32[0] = stof(��ֵ[12]); ����->Ԫ��[���Բ���]->�任.r[3].m128_f32[1] = stof(��ֵ[13]);
                ����->Ԫ��[���Բ���]->�任.r[3].m128_f32[2] = stof(��ֵ[14]); ����->Ԫ��[���Բ���]->�任.r[3].m128_f32[3] = stof(��ֵ[15]);
                break;

            case 5:
                ����->Ԫ��[���Բ���]->�������� = stoi(��ֵ[0]);
                break;

            case 6:
                ����->Ԫ��[���Բ���]->����ͼ���� = stoi(��ֵ[0]);
                break;

            case 7:
                ����->Ԫ��[���Բ���]->����.������.x = stof(��ֵ[0]); ����->Ԫ��[���Բ���]->����.������.y = stof(��ֵ[1]);
                ����->Ԫ��[���Բ���]->����.������.z = stof(��ֵ[2]); ����->Ԫ��[���Բ���]->����.������.w = stof(��ֵ[3]);
                break;

            case 8:
                ����->Ԫ��[���Բ���]->����.�Է���.x = stof(��ֵ[0]); ����->Ԫ��[���Բ���]->����.�Է���.y = stof(��ֵ[1]);
                ����->Ԫ��[���Բ���]->����.�Է���.z = stof(��ֵ[2]); ����->Ԫ��[���Բ���]->����.�Է���.w = stof(��ֵ[3]);
                break;

            case 9:
                ����->Ԫ��[���Բ���]->����.������.x = stof(��ֵ[0]); ����->Ԫ��[���Բ���]->����.������.y = stof(��ֵ[1]);
                ����->Ԫ��[���Բ���]->����.������.z = stof(��ֵ[2]); ����->Ԫ��[���Բ���]->����.������.w = stof(��ֵ[3]);
                break;

            case 10:
                ����->Ԫ��[���Բ���]->����.����� = stoi(��ֵ[0]);
                break;

            case 11:
                ����->Ԫ��[���Բ���]->����.�߹⼶�� = stoi(��ֵ[0]);
                break;

            case 12:
                ����->Ԫ��[���Բ���]->����.��͸���� = stoi(��ֵ[0]);
                break;

            case 15:
                �������� = stoi(��ֵ[0]);
                s��������->���㼯.resize(��������);
                break;

            case 16:
                s��������->���㼯[���㲽��].λ��.x = stof(��ֵ[0]); s��������->���㼯[���㲽��].λ��.y = stof(��ֵ[1]); 
                s��������->���㼯[���㲽��].λ��.z = stof(��ֵ[2]);
                break;

            case 17:
                s��������->���㼯[���㲽��].������.x = stof(��ֵ[0]); s��������->���㼯[���㲽��].������.y = stof(��ֵ[1]); 
                s��������->���㼯[���㲽��].������.z = stof(��ֵ[2]);
                break;

            case 18:
                s��������->���㼯[���㲽��].��������.x = stof(��ֵ[0]); s��������->���㼯[���㲽��].��������.y = stof(��ֵ[1]);
                ���㲽��++;
                break;

            case 19:
                ������ʽ = (DXGI_FORMAT)stoi(��ֵ[0]);
                break;

            case 20:
                �������� = stoi(��ֵ[0]);
                if (������ʽ == DXGI_FORMAT_R32_UINT)
                    s��������->����.resize(��������);

                if (������ʽ == DXGI_FORMAT_R16_UINT)
                    s��������->s����.resize(��������);

                break;

            case 21:
                if (������ʽ == DXGI_FORMAT_R32_UINT)
                {
                    s��������->����[��������] = stoi(��ֵ[0]); s��������->����[�������� + 1] = stoi(��ֵ[1]); 
                    s��������->����[�������� + 2] = stoi(��ֵ[2]);
                    �������� += 3;
                }
                if (������ʽ == DXGI_FORMAT_R16_UINT)
                {
                    s��������->s����[��������] = stoi(��ֵ[0]); s��������->s����[�������� + 1] = stoi(��ֵ[1]); 
                    s��������->s����[�������� + 2] = stoi(��ֵ[2]);
                    �������� += 3;
                }
                break;

            case 22:
                i = 0;
                while (�ļ�����[i] != '\0')
                {
                    ͼƬ����w[i] = �ļ�����[i];
                    i++;
                }
                ���� = WideCharToMultiByte(CP_ACP, 0, ͼƬ����w, wcslen(ͼƬ����w), ͼƬ����, 128, 0, 0);
                ͼƬ����[����] = '\0';
                
                i = strlen(ͼƬ����);
                while (1)
                {
                    i--;
                    if (ͼƬ����[i] == '/')
                    {
                        ͼƬ����[i] = '\0';
                        break;
                    }
                    else if (ͼƬ����[i] == '\\')
                    {
                        ͼƬ����[i] = '\0';
                        break;
                    }
                }

                ����·�� = ͼƬ����;

                �ַ������� = WideCharToMultiByte(CP_ACP, 0, ��ֵ[0].c_str(), wcslen(��ֵ[0].c_str()), ͼƬ����, 128, 0, 0);
                ͼƬ����[�ַ�������] = 0;

                ����·�� += "//"; 
                ����·�� += ͼƬ����;

                for (i = 0; i < s��������->·����.size(); i++)
                {
                    char ·��[128]{};
                    int ���� = WideCharToMultiByte(CP_ACP, 0, s��������->·����[i].c_str(), s��������->·����[i].size(), ·��, 128, 0, 0);
                    ·��[����] = 0;

                    if (����·�� == ·��)
                    {
                        goto ����;
                    }
                }

                ���� = MultiByteToWideChar(CP_ACP, 0, ����·��.c_str(), ����·��.size(), ����·��w, 128);
                ����·��w[����] = 0;

                s��������->·����.push_back(����·��w);

                �ļ�����.clear();
                �Ƿ���¼ = 0;
                for (int i = 0; i < wcslen(����·��w); i++)
                {
                    if (�Ƿ���¼) �ļ����� += ����·��w[i];
                    if (����·��w[i] == '.')
                    {
                        �Ƿ���¼ = 1;
                        �ļ�����.clear();
                    }
                }

                ����->����.resize(����->����.size() + 1);
                ����->�����ϴ�.resize(����->�����ϴ�.size() + 1);
                if (�ļ����� == L"dds")
                {
                    if (!SUCCEEDED(CreateDDSTextureFromFile12(�豸.Get(), �������.Get(), ����·��w,
                        this->����->����[this->����->����.size() - 1], this->����->�����ϴ�[this->����->�����ϴ�.size() - 1])))
                    {
                        wstring bug = L"����mds�ļ�ʱ�Ҳ�����ͼ line:" + to_wstring(__LINE__) + L'\n';
                        OutputDebugString(bug.c_str());
                        PostQuitMessage(0);
                    }
                }
                else
                {
                    if (!SUCCEEDED(CreateImageDataTextureFromFile(�豸.Get(), �������.Get(), ����·��w,
                        this->����->����[this->����->����.size() - 1], this->����->�����ϴ�[this->����->�����ϴ�.size() - 1])))
                    {
                        wstring bug = L"����ģ�Ͳ���ʱδ�ҵ���ͼ�ļ� line:";
                        bug += to_wstring(__LINE__) + L"\n";
                        OutputDebugString(bug.c_str());
                        PostQuitMessage(0);
                    }
                }

                ����:
                break;

            case 23:
                ����->Ԫ��[���Բ���]->��Χ��.Center.x = stof(��ֵ[0]); ����->Ԫ��[���Բ���]->��Χ��.Center.y = stof(��ֵ[1]);
                ����->Ԫ��[���Բ���]->��Χ��.Center.z = stof(��ֵ[2]);
                break;

            case 24:
                ����->Ԫ��[���Բ���]->��Χ��.Radius = stof(��ֵ[0]);
                break;

            case 25:
                s��������->��Χ���[���Բ���].resize(stoi(��ֵ[0]));
                ��Χ���� = 0;
                ���Բ���++;
                break;

            case 26:
                s��������->��Χ���[���Բ��� - 1][��Χ����].����ǰλ��.x = stof(��ֵ[0]);
                s��������->��Χ���[���Բ��� - 1][��Χ����].����ǰλ��.y = stof(��ֵ[1]);
                s��������->��Χ���[���Բ��� - 1][��Χ����].����ǰλ��.z = stof(��ֵ[2]);
                break;

            case 27:
                s��������->��Χ���[���Բ��� - 1][��Χ����].�߳�.x = stof(��ֵ[0]);
                s��������->��Χ���[���Բ��� - 1][��Χ����].�߳�.y = stof(��ֵ[1]);
                s��������->��Χ���[���Բ��� - 1][��Χ����].�߳�.z = stof(��ֵ[2]);
                ��Χ����++;
                break;

            default:
                break;
            }

    }

    �����ļ�.close();

    ���㲼�� = FVFλ�� | FVF������ | FVF��������;
    ���㵥Ԫ��С = sizeof(S����);

    D3D12_HEAP_PROPERTIES HeapProperties = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT);
    D3D12_RESOURCE_DESC Desc = CD3DX12_RESOURCE_DESC::Buffer(sizeof(S����) * s��������->���㼯.size());
    �豸->CreateCommittedResource(
        &HeapProperties,
        D3D12_HEAP_FLAG_NONE,
        &Desc,
        D3D12_RESOURCE_STATE_COMMON,
        nullptr,
        IID_PPV_ARGS(&����));

    HeapProperties = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
    Desc = CD3DX12_RESOURCE_DESC::Buffer(sizeof(S����) * s��������->���㼯.size());
    �豸->CreateCommittedResource(
        &HeapProperties,
        D3D12_HEAP_FLAG_NONE,
        &Desc,
        D3D12_RESOURCE_STATE_GENERIC_READ,
        nullptr,
        IID_PPV_ARGS(&�����ϴ�));

    D3D12_SUBRESOURCE_DATA subResourceData = {};
    subResourceData.pData = s��������->���㼯.data();
    subResourceData.RowPitch = sizeof(S����) * s��������->���㼯.size();
    subResourceData.SlicePitch = subResourceData.RowPitch;

    D3D12_RESOURCE_BARRIER pBarriers = CD3DX12_RESOURCE_BARRIER::Transition(����.Get(),
        D3D12_RESOURCE_STATE_COMMON, D3D12_RESOURCE_STATE_COPY_DEST);
    �������->ResourceBarrier(1, &pBarriers);
    UpdateSubresources<1>(�������.Get(), ����.Get(), �����ϴ�.Get(), 0, 0, 1, &subResourceData);
    pBarriers = CD3DX12_RESOURCE_BARRIER::Transition(����.Get(),
        D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_GENERIC_READ);
    �������->ResourceBarrier(1, &pBarriers);

    vbv.BufferLocation = ����->GetGPUVirtualAddress();
    vbv.StrideInBytes = sizeof(S����);
    vbv.SizeInBytes = sizeof(S����) * s��������->���㼯.size();

    switch (������ʽ)
    {
    case DXGI_FORMAT_R32_UINT:
        HeapProperties = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT);
        Desc = CD3DX12_RESOURCE_DESC::Buffer(sizeof(UINT) * s��������->����.size());
        �豸->CreateCommittedResource(
            &HeapProperties,
            D3D12_HEAP_FLAG_NONE,
            &Desc,
            D3D12_RESOURCE_STATE_COMMON,
            nullptr,
            IID_PPV_ARGS(&����));

        HeapProperties = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
        Desc = CD3DX12_RESOURCE_DESC::Buffer(sizeof(UINT) * s��������->����.size());
        �豸->CreateCommittedResource(
            &HeapProperties,
            D3D12_HEAP_FLAG_NONE,
            &Desc,
            D3D12_RESOURCE_STATE_GENERIC_READ,
            nullptr,
            IID_PPV_ARGS(&�����ϴ�));

        ibv.SizeInBytes = sizeof(UINT) * ��������;
        ibv.Format = DXGI_FORMAT_R32_UINT;
        break;

    case DXGI_FORMAT_R16_UINT:
        HeapProperties = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT);
        Desc = CD3DX12_RESOURCE_DESC::Buffer(sizeof(USHORT) * s��������->s����.size());
        �豸->CreateCommittedResource(
            &HeapProperties,
            D3D12_HEAP_FLAG_NONE,
            &Desc,
            D3D12_RESOURCE_STATE_COMMON,
            nullptr,
            IID_PPV_ARGS(&����));

        HeapProperties = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
        Desc = CD3DX12_RESOURCE_DESC::Buffer(sizeof(USHORT) * s��������->s����.size());
        �豸->CreateCommittedResource(
            &HeapProperties,
            D3D12_HEAP_FLAG_NONE,
            &Desc,
            D3D12_RESOURCE_STATE_GENERIC_READ,
            nullptr,
            IID_PPV_ARGS(&�����ϴ�));

        ibv.SizeInBytes = sizeof(USHORT) * ��������;
        ibv.Format = DXGI_FORMAT_R16_UINT;
        break;

    default:

        break;
    }

    if (������ʽ == DXGI_FORMAT_R16_UINT)
    {
        subResourceData.RowPitch = sizeof(USHORT) * s��������->s����.size();
        subResourceData.pData = s��������->s����.data();
    }
    else if(������ʽ == DXGI_FORMAT_R32_UINT)
    {
        subResourceData.RowPitch = sizeof(UINT) * s��������->����.size();
        subResourceData.pData = s��������->����.data();
    }

    subResourceData.SlicePitch = subResourceData.RowPitch;

    pBarriers = CD3DX12_RESOURCE_BARRIER::Transition(����.Get(),
        D3D12_RESOURCE_STATE_COMMON, D3D12_RESOURCE_STATE_COPY_DEST);
    �������->ResourceBarrier(1, &pBarriers);
    UpdateSubresources<1>(�������.Get(), ����.Get(), �����ϴ�.Get(), 0, 0, 1, &subResourceData);
    pBarriers = CD3DX12_RESOURCE_BARRIER::Transition(����.Get(),
        D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_GENERIC_READ);
    �������->ResourceBarrier(1, &pBarriers);

    ibv.BufferLocation = ����->GetGPUVirtualAddress();

    ������Χ�򻺴�();
    ��������������();
}

//����fbx��̬�ļ�-----------------------------------------------------------------------------------
void C��̬����::����FBX�ļ�(const WCHAR* �ļ�·��, wstring �������Ƽ�, DXGI_FORMAT ������ʽ, float ��������)
{
    FbxManager* lFBX���� = NULL;
    FbxScene* l���� = NULL;

    this->������ʽ = ������ʽ;
    this->�������Ƽ� = �������Ƽ�;

    s�������� = new S��������;

    lFBX���� = FbxManager::Create();
    FbxIOSettings* ���� = FbxIOSettings::Create(lFBX����, IOSROOT);
    lFBX����->SetIOSettings(����);
    FbxImporter* l���� = FbxImporter::Create(lFBX����, "");

    char* �ļ����� = 0;
    FbxWCToUTF8(�ļ�·��, �ļ�����, 0);
    if (!l����->Initialize(�ļ�����, -1, ����))
    {
        char ����[100];
        sprintf_s(����, "fbx�������: %s, line:%d\n", l����->GetStatus().GetErrorString(), __LINE__);
        OutputDebugStringA(����);
        PostQuitMessage(0);
        return;
    }

    l���� = FbxScene::Create(lFBX����, "myScene");
    l����->Import(l����);
    l����->Destroy();

    FbxNode* ���ڵ� = l����->GetRootNode();
    ���� = new C��������;
    ����->����.resize(1);
    ����->����[0] = nullptr;
    ����->�����ϴ�.resize(1);
    ����->�����ϴ�[0] = nullptr;
    ����->������ͼ��.resize(1);
    ����->������ͼ��[0] = nullptr;
    if (���ڵ�)
    {
        for (int i = 0; i < ���ڵ�->GetChildCount(); i++)
            ���ؽڵ�(���ڵ�->GetChild(i));
    }

    �Ż�����();
    for (int i = 0; i < m���ƶ��㼯.size(); i++)
        �ͷ�����(m���ƶ��㼯[i]);

    s��������->���㼯.resize(m�Ż����㼯.size());
    for (int i = 0; i < m�Ż����㼯.size(); i++)
    {
        s��������->���㼯[i] = m�Ż����㼯[i].����;
    }

    �������� = s��������->���㼯.size();

    D3D12_HEAP_PROPERTIES HeapProperties = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT);
    D3D12_RESOURCE_DESC Desc = CD3DX12_RESOURCE_DESC::Buffer(sizeof(S����) * s��������->���㼯.size());
    �豸->CreateCommittedResource(
        &HeapProperties,
        D3D12_HEAP_FLAG_NONE,
        &Desc,
        D3D12_RESOURCE_STATE_COMMON,
        nullptr,
        IID_PPV_ARGS(&����));

    HeapProperties = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
    Desc = CD3DX12_RESOURCE_DESC::Buffer(sizeof(S����) * s��������->���㼯.size());
    �豸->CreateCommittedResource(
        &HeapProperties,
        D3D12_HEAP_FLAG_NONE,
        &Desc,
        D3D12_RESOURCE_STATE_GENERIC_READ,
        nullptr,
        IID_PPV_ARGS(&�����ϴ�));

    D3D12_SUBRESOURCE_DATA subResourceData = {};
    subResourceData.pData = s��������->���㼯.data();
    subResourceData.RowPitch = sizeof(S����) * s��������->���㼯.size();
    subResourceData.SlicePitch = subResourceData.RowPitch;

    D3D12_RESOURCE_BARRIER pBarriers = CD3DX12_RESOURCE_BARRIER::Transition(����.Get(),
        D3D12_RESOURCE_STATE_COMMON, D3D12_RESOURCE_STATE_COPY_DEST);
    �������->ResourceBarrier(1, &pBarriers);
    UpdateSubresources<1>(�������.Get(), ����.Get(), �����ϴ�.Get(), 0, 0, 1, &subResourceData);
    pBarriers = CD3DX12_RESOURCE_BARRIER::Transition(����.Get(),
        D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_GENERIC_READ);
    �������->ResourceBarrier(1, &pBarriers);

    vbv.BufferLocation = ����->GetGPUVirtualAddress();
    vbv.StrideInBytes = sizeof(S����);
    vbv.SizeInBytes = sizeof(S����) * s��������->���㼯.size();

    switch (������ʽ)
    {
    case DXGI_FORMAT_R32_UINT:
        HeapProperties = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT);
        Desc = CD3DX12_RESOURCE_DESC::Buffer(sizeof(UINT) * s��������->����.size());
        �豸->CreateCommittedResource(
            &HeapProperties,
            D3D12_HEAP_FLAG_NONE,
            &Desc,
            D3D12_RESOURCE_STATE_COMMON,
            nullptr,
            IID_PPV_ARGS(&����));

        HeapProperties = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
        Desc = CD3DX12_RESOURCE_DESC::Buffer(sizeof(UINT) * s��������->����.size());
        �豸->CreateCommittedResource(
            &HeapProperties,
            D3D12_HEAP_FLAG_NONE,
            &Desc,
            D3D12_RESOURCE_STATE_GENERIC_READ,
            nullptr,
            IID_PPV_ARGS(&�����ϴ�));

        ibv.SizeInBytes = sizeof(UINT) * ��������;
        ibv.Format = DXGI_FORMAT_R32_UINT;
        break;

    case DXGI_FORMAT_R16_UINT:
        HeapProperties = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT);
        Desc = CD3DX12_RESOURCE_DESC::Buffer(sizeof(USHORT) * s��������->����.size());
        �豸->CreateCommittedResource(
            &HeapProperties,
            D3D12_HEAP_FLAG_NONE,
            &Desc,
            D3D12_RESOURCE_STATE_COMMON,
            nullptr,
            IID_PPV_ARGS(&����));

        HeapProperties = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
        Desc = CD3DX12_RESOURCE_DESC::Buffer(sizeof(USHORT) * s��������->����.size());
        �豸->CreateCommittedResource(
            &HeapProperties,
            D3D12_HEAP_FLAG_NONE,
            &Desc,
            D3D12_RESOURCE_STATE_GENERIC_READ,
            nullptr,
            IID_PPV_ARGS(&�����ϴ�));

        ibv.SizeInBytes = sizeof(USHORT) * ��������;
        ibv.Format = DXGI_FORMAT_R16_UINT;
        break;

    default:

        break;
    }

    if (������ʽ == DXGI_FORMAT_R16_UINT)
    {
        s��������->s����.resize(s��������->����.size());
        for (int i = 0; i < s��������->����.size(); i++)
            s��������->s����[i] = s��������->����[i];
        subResourceData.pData = s��������->s����.data();
        subResourceData.RowPitch = sizeof(USHORT) * s��������->s����.size();
    }
    else if(������ʽ == DXGI_FORMAT_R32_UINT)
    {
        subResourceData.pData = s��������->����.data();
        subResourceData.RowPitch = sizeof(UINT) * s��������->����.size();
    }

    subResourceData.SlicePitch = subResourceData.RowPitch;

    pBarriers = CD3DX12_RESOURCE_BARRIER::Transition(����.Get(),
        D3D12_RESOURCE_STATE_COMMON, D3D12_RESOURCE_STATE_COPY_DEST);
    �������->ResourceBarrier(1, &pBarriers);
    UpdateSubresources<1>(�������.Get(), ����.Get(), �����ϴ�.Get(), 0, 0, 1, &subResourceData);
    pBarriers = CD3DX12_RESOURCE_BARRIER::Transition(����.Get(),
        D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_GENERIC_READ);
    �������->ResourceBarrier(1, &pBarriers);

    ibv.BufferLocation = ����->GetGPUVirtualAddress();

    ���ػ�(��������);
    ������Χ�򻺴�();
    ������Χ��();
    ��������������();

    �ͷźϲ���Ϣ();
    lFBX����->Destroy();
}

void C��̬����::���ؽڵ�(FbxNode* p�ڵ�)
{
    FbxNodeAttribute::EType l�ڵ�����{};

    if (p�ڵ�->GetNodeAttribute())
    {
        l�ڵ����� = p�ڵ�->GetNodeAttribute()->GetAttributeType();

        switch (l�ڵ�����)
        {
        case FbxNodeAttribute::eSkeleton:

            break;

        case FbxNodeAttribute::eMesh:
            ��������(p�ڵ�);
            break;

        default:
            break;
        }
    }

    for (int i = 0; i < p�ڵ�->GetChildCount(); ++i)
    {
        ���ؽڵ�(p�ڵ�->GetChild(i));
    }
}

void C��̬����::���ؽڵ�(FbxScene* p����)
{
    int i;
    FbxNode* p�ڵ� = p����->GetRootNode();

    if (p�ڵ�)
    {
        for (i = 0; i < p�ڵ�->GetChildCount(); i++)
        {
            ���ؽڵ�(p�ڵ�->GetChild(i));
        }
    }
}

void C��̬����::��������(FbxNode* p����ڵ�)
{
    FbxMesh* p���� = p����ڵ�->GetMesh();
    if (p���� == NULL) return;
    int i = 0;
    int j = 0;
    int k = 0;

    UINT l��ǰ�������� = 0;
    UINT l��ǰ������� = 0;
    UINT l��������� = p����->GetPolygonCount();
    for (i = 0; i < l���������; i++)
    {
        int ��ǰ����ζ������� = p����->GetPolygonSize(i);
        �������� += (��ǰ����ζ������� - 2) * 3;
        l��ǰ�������� += (��ǰ����ζ������� - 2) * 3;
    }

    s��������->����.resize(��������);
    m���ƶ��㼯.resize(m���ƶ��㼯.size() + p����->GetControlPointsCount());
    //��ʼ������
    for (i = m���ƶ��㼯.size() - p����->GetControlPointsCount(); i < m���ƶ��㼯.size(); i++)
        m���ƶ��㼯[i] = new S��������;

    for (i = 0; i < l���������; i++)
    {
        UINT ����ζ������� = 0;
        ����ζ������� = p����->GetPolygonSize(i);
        for (j = 0; j < ����ζ�������; j++)
        {
            int l���ƶ������� = p����->GetPolygonVertex(i, j);
            int id;
            FbxVector4* l���ƶ��� = p����->GetControlPoints();
            S���� l����{};

            l����.λ��.z = l���ƶ���[l���ƶ�������].mData[0];
            l����.λ��.x = l���ƶ���[l���ƶ�������].mData[1];
            l����.λ��.y = l���ƶ���[l���ƶ�������].mData[2];

            FbxGeometryElementUV* p�������� = p����->GetElementUV(0);

            if(p��������)
                switch (p��������->GetMappingMode())
                {
                case FbxGeometryElement::eByControlPoint:
                    switch (p��������->GetReferenceMode())
                    {
                    case FbxGeometryElement::eDirect:
                        l����.��������.x = p��������->GetDirectArray().GetAt(l���ƶ�������).mData[0];
                        l����.��������.y = 1.0f - p��������->GetDirectArray().GetAt(l���ƶ�������).mData[1];
                        break;

                    case FbxGeometryElement::eIndexToDirect:
                        id = p��������->GetIndexArray().GetAt(l���ƶ�������);
                        l����.��������.x = p��������->GetDirectArray().GetAt(id).mData[0];
                        l����.��������.y = 1.0f - p��������->GetDirectArray().GetAt(id).mData[1];
                        break;

                    default:
                        break;
                    }
                    break;

                case FbxGeometryElement::eByPolygonVertex:
                    switch (p��������->GetReferenceMode())
                    {
                    case FbxGeometryElement::eDirect:
                    case FbxGeometryElement::eIndexToDirect:
                        l����.��������.x = p��������->GetDirectArray().GetAt(p����->GetTextureUVIndex(i, j)).mData[0];
                        l����.��������.y = 1.0f - p��������->GetDirectArray().GetAt(p����->GetTextureUVIndex(i, j)).mData[1];
                        break;

                    default:
                        break;
                    }
                    break;
                }

            FbxGeometryElementNormal* p������ = p����->GetElementNormal(0);
            switch (p������->GetMappingMode())
            {
            case FbxGeometryElement::eByControlPoint:
                switch (p������->GetReferenceMode())
                {
                case FbxGeometryElement::eDirect:
                    l����.������.z = p������->GetDirectArray().GetAt(l���ƶ�������).mData[0];
                    l����.������.x = p������->GetDirectArray().GetAt(l���ƶ�������).mData[1];
                    l����.������.y = p������->GetDirectArray().GetAt(l���ƶ�������).mData[2];
                    break;

                case FbxGeometryElement::eIndexToDirect:
                    id = p������->GetIndexArray().GetAt(l���ƶ�������);
                    l����.������.z = p������->GetDirectArray().GetAt(id).mData[0];
                    l����.������.x = p������->GetDirectArray().GetAt(id).mData[1];
                    l����.������.y = p������->GetDirectArray().GetAt(id).mData[2];
                    break;

                default:
                    break;
                }
                break;

            case FbxGeometryElement::eByPolygonVertex:
                switch (p������->GetReferenceMode())
                {
                case FbxGeometryElement::eDirect:
                    l����.������.z = p������->GetDirectArray().GetAt(l��ǰ�������).mData[0];
                    l����.������.x = p������->GetDirectArray().GetAt(l��ǰ�������).mData[1];
                    l����.������.y = p������->GetDirectArray().GetAt(l��ǰ�������).mData[2];
                    break;

                case FbxGeometryElement::eIndexToDirect:
                    id = p������->GetIndexArray().GetAt(l��ǰ�������);
                    l����.������.z = p������->GetDirectArray().GetAt(id).mData[0];
                    l����.������.x = p������->GetDirectArray().GetAt(id).mData[1];
                    l����.������.y = p������->GetDirectArray().GetAt(id).mData[2];
                    break;

                default:
                    break;
                }
                break;
            }

            ��Ӷ���(m���ƶ��㼯[m���ƶ��㼯.size() - p����->GetControlPointsCount() + l���ƶ�������], l����, m�������);
            m�������++;
            l��ǰ�������++;
        }

        for (k = 0; k < ����ζ������� - 2; k++)
        {
            s��������->����[m��������] = m������� - ����ζ�������;
            m��������++;
            s��������->����[m��������] = m������� - k - 1;
            m��������++;
            s��������->����[m��������] = m������� - k - 2;
            m��������++;
        }
    }

    C��������::S����* ���� = new C��������::S����;

    ���ز���(p����ڵ�, ����);

    FbxMesh* l���� = (FbxMesh*)p����ڵ�->GetNodeAttribute();

    ����->�������� = l��ǰ��������;
    ����->��ʼ���� = m�������� - l��ǰ��������;
    XMMATRIX �任���� = XMMatrixIdentity();
    �任���� = XMMatrixScaling(p����ڵ�->LclScaling.Get().mData[1], p����ڵ�->LclScaling.Get().mData[2],
        p����ڵ�->LclScaling.Get().mData[0]);
    �任���� *= XMMatrixRotationRollPitchYaw(p����ڵ�->LclRotation.Get().mData[1] * XM_PI / 180,
        p����ڵ�->LclRotation.Get().mData[2] * XM_PI / 180, p����ڵ�->LclRotation.Get().mData[0] * XM_PI / 180);
    �任���� *= XMMatrixTranslation(-p����ڵ�->LclTranslation.Get().mData[2], p����ڵ�->LclTranslation.Get().mData[1],
        p����ڵ�->LclTranslation.Get().mData[0]);
    ����->�任 = �任����;

    WCHAR* �������� = 0;
    FbxUTF8ToWC(p����ڵ�->GetName(), ��������, 0);
    ����->�������� = ��������;

    this->����->���Ԫ��(����);
}

void C��̬����::��Ӷ���(S��������* p����ͷ, S����& ����, UINT ����)
{
    S��������* p�ڵ� = p����ͷ;

    while (p�ڵ�->p��һ�ڵ�)
        p�ڵ� = p�ڵ�->p��һ�ڵ�;

    p�ڵ�->p��һ�ڵ� = new S��������;
    p�ڵ� = p�ڵ�->p��һ�ڵ�;

    p�ڵ�->���� = ����;
    p�ڵ�->���� = ����;
    p�ڵ�->p��һ�ڵ� = 0;
}

void C��̬����::�ͷ�����(S��������* p����ͷ)
{
    S��������* p�ڵ� = p����ͷ;
    S��������* p��һ�ڵ� = p�ڵ�->p��һ�ڵ�;

    while (p��һ�ڵ�)
    {
        p�ڵ� = p��һ�ڵ�;
        p��һ�ڵ� = p�ڵ�->p��һ�ڵ�;
        delete p�ڵ�;
        p�ڵ� = p��һ�ڵ�;
    }

    delete p�ڵ�;
    delete p����ͷ;
}

void C��̬����::���ز���(FbxNode* p����ڵ�, C��������::S����* ����)
{
    FbxMesh* p���� = p����ڵ�->GetMesh();
    WCHAR* �������� = 0;
    FbxUTF8ToWC(p����ڵ�->GetName(), ��������, 0);
    ����->�������� = ��������;
    int �������� = 0;

    this->����->����[0] = ������Դ->����ͼ;

    if (p���� && p����ڵ�)
    {
        �������� = p����ڵ�->GetMaterialCount();
    }

    if (�������� > 0)
    {
        for (int i = 0; i < ��������; i++)
        {
            FbxSurfaceMaterial* p������� = p����ڵ�->GetMaterial(i);

            ���ز�������(p�������, ����);
        }
    }
    else  //Ĭ�ϲ���
    {
        ����->����.������ = { 1.0f, 1.0f, 1.0f, 1.0f };
        ����->����.������ = { 0.0f, 0.0f, 0.0f, 1.0f };
        ����->����.�Է��� = { 0.0f, 0.0f, 0.0f, 1.0f };
        ����->����.����� = 2.0f;
        ����->����.��͸���� = 1.0f;
        ����->����.�߹⼶�� = 1.0f;
        ����->�������� = 0;
    }
}

void C��̬����::���ز�������(FbxSurfaceMaterial* p�������, C��������::S����* ����)
{
    p�������->GetName();

    if (p�������->GetClassId().Is(FbxSurfacePhong::ClassId))
    {
        FbxDouble3 ������ = ((FbxSurfacePhong*)p�������)->Diffuse;
        ����->����.������.x = ������.mData[0];
        ����->����.������.y = ������.mData[1];
        ����->����.������.z = ������.mData[2];

        FbxDouble3 �Է��� = ((FbxSurfacePhong*)p�������)->Emissive;
        ����->����.�Է���.x = �Է���.mData[0];
        ����->����.�Է���.y = �Է���.mData[1];
        ����->����.�Է���.z = �Է���.mData[2];

        FbxDouble ��͸���� = 1.0 - ((FbxSurfacePhong*)p�������)->TransparencyFactor;
        ����->����.������.w = ��͸����;

        FbxDouble ����� = ((FbxSurfacePhong*)p�������)->Shininess;
        ����->����.����� = �����;

        FbxDouble �߹�ȼ� = ((FbxSurfacePhong*)p�������)->SpecularFactor;
        ����->����.�߹⼶�� = �߹�ȼ�;
        if (����->����.�߹⼶�� < 1)����->����.�߹⼶�� = 1;

        FbxDouble ������ = 1.0 - ((FbxSurfacePhong*)p�������)->ReflectionFactor;
    }
    else if (p�������->GetClassId().Is(FbxSurfaceLambert::ClassId))
    {
        FbxDouble3 ������ = ((FbxSurfaceLambert*)p�������)->Ambient;
        ����->����.������.x = ������.mData[0];
        ����->����.������.y = ������.mData[1];
        ����->����.������.z = ������.mData[2];

        FbxDouble3 ������ = ((FbxSurfaceLambert*)p�������)->Diffuse;
        ����->����.������.x = ������.mData[0];
        ����->����.������.y = ������.mData[1];
        ����->����.������.z = ������.mData[2];

        FbxDouble3 �Է��� = ((FbxSurfaceLambert*)p�������)->Emissive;
        ����->����.�Է���.x = �Է���.mData[0];
        ����->����.�Է���.y = �Է���.mData[1];
        ����->����.�Է���.z = �Է���.mData[2];

        FbxDouble ��͸���� = 1.0 - ((FbxSurfaceLambert*)p�������)->TransparencyFactor;
        ����->����.������.w = ��͸����;
    }

    ��������(p�������, ����);
}

void C��̬����::��������(FbxSurfaceMaterial* p�������, C��������::S����* ����)
{
    int i;
    int k = 0;
    int ��� = 1;

    for (i = 0; i < FbxLayerElement::sTypeTextureCount; i++)
    {
        FbxProperty ��������;
        �������� = p�������->FindProperty(FbxLayerElement::sTextureChannelNames[i]);
        if (��������.IsValid())
        {
            int textureCount = ��������.GetSrcObjectCount();

            for (int j = 0; j < textureCount; ++j)
            {
                FbxFileTexture* p���� = FbxCast<FbxFileTexture>(��������.GetSrcObject(j));
                if (p����)
                {
                    WCHAR* ·�� = 0;
                    FbxUTF8ToWC(p����->GetFileName(), ·��, 0);
                    for (k = 0; k < s��������->·����.size(); k++)
                    {
                        if (s��������->·����[k].compare(·��) == 0 && ����->�������� == 0)
                        {
                            ����->�������� = k + 1;
                            break;
                        }
                    }

                    if (����->�������� == 0)
                    {
                        s��������->·����.resize(s��������->·����.size() + 1);
                        s��������->·����[s��������->·����.size() - 1] = ·��;

                        this->����->����.resize(this->����->����.size() + 1);
                        this->����->�����ϴ�.resize(this->����->�����ϴ�.size() + 1);
                        HRESULT hr = 0;

                        wstring �ļ�����;
                        bool �Ƿ���¼ = 0;
                        for (int i = 0; i < wcslen(·��); i++)
                        {
                            if (�Ƿ���¼) �ļ����� += ·��[i];
                            if (·��[i] == '.')
                            {
                                �Ƿ���¼ = 1;
                                �ļ�����.clear();
                            }
                        }

                        if (�ļ����� == L"dds")
                        {
                            if (!SUCCEEDED(hr = CreateDDSTextureFromFile12(�豸.Get(), �������.Get(), ·��,
                                this->����->����[this->����->����.size() - 1], this->����->�����ϴ�[this->����->�����ϴ�.size() - 1])))
                            {
                                wstring bug = L"����ģ�Ͳ���ʱδ�ҵ���ͼ�ļ� line:" + to_wstring(__LINE__) + L'\n';
                                OutputDebugString(bug.c_str());
                                PostQuitMessage(0);
                            }
                        }
                        else
                        {
                            if (!SUCCEEDED(CreateImageDataTextureFromFile(�豸.Get(), �������.Get(), ·��, this->����->����[this->����->����.size() - 1],
                                this->����->�����ϴ�[this->����->�����ϴ�.size() - 1])))
                            {
                                wstring bug = L"����ģ�Ͳ���ʱδ�ҵ���ͼ�ļ� line:";
                                bug += to_wstring(__LINE__) + L"\n";
                                OutputDebugString(bug.c_str());
                                PostQuitMessage(0);
                            }
                        }
                        ����->�������� = this->����->����.size() - 1;
                    }
                }
            }
        }
    }
}

void C��̬����::�Ż�����()
{
    float ��Сcos�Ƕ� = cosf(�������ϲ����Ƕ�);
    UINT i = 0;
    UINT j = 0;
    UINT k = 0;

    for (i = 0; i < m���ƶ��㼯.size(); i++)
    {
        �ϲ�����(m���ƶ��㼯[i], ��Сcos�Ƕ�, ��ͼ������������);
    }

    for (i = 0; i < ��������; i++)
    {
        for (j = 0; j < m�ϲ�������.size(); j++)
        {
            for (k = 0; k < m�ϲ�������[j].��������.size(); k++)
            {
                if (s��������->����[i] == m�ϲ�������[j].��������[k])
                {
                    s��������->����[i] = m�ϲ�������[j].������;
                    goto ����ѭ��;
                }
            }
        }
    ����ѭ��:
        continue;
    }
}

void C��̬����::�ϲ�����(S��������* p����ͷ, float ��Сcos�Ƕ�, float ���uv���)
{
    S��������* p�ڵ� = p����ͷ;
    UINT i = 0;
    UINT j = 0;
    UINT k = 0;

    UINT �ڵ����� = 0;
    while (p�ڵ�->p��һ�ڵ�)
    {
        p�ڵ� = p�ڵ�->p��һ�ڵ�;
        �ڵ�����++;
    }
    vector<S�Ż����㼯> ���㼯;
    ���㼯.resize(�ڵ�����);

    UINT ��ǰ���� = 0;
    p�ڵ� = p����ͷ;
    while (p�ڵ�->p��һ�ڵ�)
    {
        p�ڵ� = p�ڵ�->p��һ�ڵ�;
        ���㼯[��ǰ����].���� = p�ڵ�->����;
        ���㼯[��ǰ����].���� = p�ڵ�->����;
        ��ǰ����++;
    }

    XMVECTOR ������1, ������2;
    XMVECTOR ����1, ����2;

    for (i = 0; i < �ڵ�����; i++)
    {
        for (j = i + 1; j < �ڵ�����; j++)
        {
            ������1 = XMLoadFloat3(&���㼯[i].����.������);
            ������2 = XMLoadFloat3(&���㼯[j].����.������);
            ����1 = XMLoadFloat2(&���㼯[i].����.��������);
            ����2 = XMLoadFloat2(&���㼯[j].����.��������);

            if (XMVector3Dot(������1, ������2).m128_f32[0] < ��Сcos�Ƕ� ||
                XMVector2Length(����1 - ����2).m128_f32[0] > ���uv���)
            {
                for (k = 0; k < �ڵ�����; k++)
                {
                    m�Ż����㼯.resize(m�Ż����㼯.size() + 1);
                    m�Ż����㼯[m�Ż����㼯.size() - 1].����.λ�� = ���㼯[k].����.λ��;
                    m�Ż����㼯[m�Ż����㼯.size() - 1].����.������ = ���㼯[k].����.������;
                    m�Ż����㼯[m�Ż����㼯.size() - 1].����.�������� = ���㼯[k].����.��������;
                    m�Ż����㼯[m�Ż����㼯.size() - 1].���� = ���㼯[k].����;

                    m�ϲ�������.resize(m�ϲ�������.size() + 1);
                    m�ϲ�������[m�ϲ�������.size() - 1].������ = m�Ż����㼯.size() - 1;
                    m�ϲ�������[m�ϲ�������.size() - 1].��������.push_back(���㼯[k].����);
                }
                goto ����;
            }
        }
    }

    m�ϲ�������.resize(m�ϲ�������.size() + 1);
    m�ϲ�������[m�ϲ�������.size() - 1].������ = m�Ż����㼯.size();
    m�ϲ�������[m�ϲ�������.size() - 1].��������.resize(�ڵ�����);

    ������1 = { 0.0f, 0.0f, 0.0f, 0.0f };
    for (i = 0; i < �ڵ�����; i++)
    {
        m�ϲ�������[m�ϲ�������.size() - 1].��������[i] = ���㼯[i].����;
        ������1 += XMLoadFloat3(&���㼯[i].����.������);
    }
    ������1 = ������1 / �ڵ�����;

    m�Ż����㼯.resize(m�Ż����㼯.size() + 1);
    m�Ż����㼯[m�Ż����㼯.size() - 1].����.λ�� = ���㼯[0].����.λ��;
    XMStoreFloat3(&m�Ż����㼯[m�Ż����㼯.size() - 1].����.������, ������1);
    m�Ż����㼯[m�Ż����㼯.size() - 1].����.�������� = ���㼯[0].����.��������;
    m�Ż����㼯[m�Ż����㼯.size() - 1].���� = ���㼯[0].����;

����:
    return;
}

void C��̬����::���ػ�(float ����)
{
    vector<XMFLOAT3> ���ϵ�;
    vector<XMFLOAT3> ���µ�;
    vector<XMFLOAT3> �����;
    vector<XMFLOAT3> ���ҵ�;
    vector<XMFLOAT3> ��ǰ��;
    vector<XMFLOAT3> ����;
    UINT �任���� = 0;

    m���ؿ�.resize(����->Ԫ��.size());
    ���ϵ�.resize(����->Ԫ��.size());
    ���µ�.resize(����->Ԫ��.size());
    �����.resize(����->Ԫ��.size());
    ���ҵ�.resize(����->Ԫ��.size());
    ��ǰ��.resize(����->Ԫ��.size());
    ����.resize(����->Ԫ��.size());
    for (int i = 0; i < ����->Ԫ��.size(); i++)
    {
        m���ؿ�[i] = new S���ؿ�;
        m���ؿ�[i]->��� = (float)1 / ����;

        //�߽���
        ����[i] = s��������->���㼯[i].λ��;

        XMVECTOR v���� = { ����[i].x, ����[i].y, ����[i].z, 1.0f };
        v���� = XMVector3Transform(v����, ����->Ԫ��[0]->�任);
        ����[i].x = v����.m128_f32[0]; ����[i].y = v����.m128_f32[1]; ����[i].z = v����.m128_f32[2];
        ��ǰ��[i] = ���ҵ�[i] = �����[i] = ���µ�[i] = ���ϵ�[i] = ����[i];

        XMFLOAT3 ��{};

        if (������ʽ == DXGI_FORMAT_R32_UINT)
        {
            for (int j = ����->Ԫ��[�任����]->��ʼ����; j < ����->Ԫ��[�任����]->��ʼ���� + ����->Ԫ��[�任����]->��������; j++)
            {
                �� = s��������->���㼯[s��������->����[j]].λ��;

                if (���ϵ�[i].y < ��.y) ���ϵ�[i] = ��;
                if (���µ�[i].y > ��.y) ���µ�[i] = ��;
                if (�����[i].z > ��.z) �����[i] = ��;
                if (���ҵ�[i].z < ��.z) ���ҵ�[i] = ��;
                if (��ǰ��[i].x > ��.x) ��ǰ��[i] = ��;
                if (����[i].x < ��.x) ����[i] = ��;
            }

            �任����++;
        }
        else if (������ʽ == DXGI_FORMAT_R16_UINT)
        {
            for (int j = ����->Ԫ��[�任����]->��ʼ����; j < ����->Ԫ��[�任����]->��ʼ���� + ����->Ԫ��[�任����]->��������; j++)
            {
                �� = s��������->���㼯[s��������->s����[j]].λ��;

                if (���ϵ�[i].y < ��.y) ���ϵ�[i] = ��;
                if (���µ�[i].y > ��.y) ���µ�[i] = ��;
                if (�����[i].z > ��.z) �����[i] = ��;
                if (���ҵ�[i].z < ��.z) ���ҵ�[i] = ��;
                if (��ǰ��[i].x > ��.x) ��ǰ��[i] = ��;
                if (����[i].x < ��.x) ����[i] = ��;
            }

            �任����++;
        }

        int �� = 0;
        �� = (int)����[i].x - (int)��ǰ��[i].x + 2;

        int �� = 0;
        �� = (int)���ϵ�[i].y - (int)���µ�[i].y + 2;

        int �� = 0;
        �� = (int)���ҵ�[i].z - (int)�����[i].z + 2;

        m���ؿ�[i]->�߸���[0] = �� * ����;  m���ؿ�[i]->�߸���[1] = �� * ����;  m���ؿ�[i]->�߸���[2] = �� * ����;

        m���ؿ�[i]->���� = new bool** [m���ؿ�[i]->�߸���[2]];
        for (int m = 0; m < m���ؿ�[i]->�߸���[2]; m++)
        {
            m���ؿ�[i]->����[m] = new bool* [m���ؿ�[i]->�߸���[1]];
            for (int j = 0; j < m���ؿ�[i]->�߸���[1]; j++)
            {
                m���ؿ�[i]->����[m][j] = new bool[m���ؿ�[i]->�߸���[0]];
                for (int k = 0; k < m���ؿ�[i]->�߸���[0]; k++)
                    m���ؿ�[i]->����[m][j][k] = 0;
            }
        }
    }

    for(int i = 0; i < ����->Ԫ��.size(); i++)
    {
        float ��� = 1.0f / ����;

        m���ؿ�[i]->���½�λ��.z = (float)(int)(�����[i].z - 1); m���ؿ�[i]->���½�λ��.y = (float)(int)(���µ�[i].y - 1);
        m���ؿ�[i]->���½�λ��.x = (float)(int)(��ǰ��[i].x - 1);

        //����
        XMFLOAT3 ������ = XMFLOAT3{ m���ؿ�[i]->���½�λ��.x, m���ؿ�[i]->���½�λ��.y, m���ؿ�[i]->���½�λ��.z };
        �任���� = 0;
        int �߳��� = thread::hardware_concurrency();
        vector<thread> �߳�;
        �߳�.resize(�߳���);
        UINT ���� = 0;

        if (������ʽ == DXGI_FORMAT_R32_UINT)
        {
            for (int z = 0; z < m���ؿ�[i]->�߸���[2]; z++)
            {
                ������.y = m���ؿ�[i]->���½�λ��.y;
                for (int y = 0; y < m���ؿ�[i]->�߸���[1]; y++)
                {
                    ������.x = m���ؿ�[i]->���½�λ��.x;
                    for (int x = 0; x < m���ؿ�[i]->�߸���[0]; x++)
                    {
                        �߳�[����] = thread(���ز����߳�, s��������, ����, m���ؿ�, ������, i, x, y, z);
                        ����++;

                        if (���� == �߳���)
                        {
                            ���� = 0;
                            for (int n = 0; n < �߳���; n++)
                                if (�߳�[n].joinable()) �߳�[n].join();
                        }

                        ������.x += ���;
                    }
                    ������.y += ���;
                }
                ������.z += ���;
            }
        }
        else if (������ʽ == DXGI_FORMAT_R16_UINT)
        {
            for (int z = 0; z < m���ؿ�[i]->�߸���[2]; z++)
            {
                ������.y = m���ؿ�[i]->���½�λ��.y;
                for (int y = 0; y < m���ؿ�[i]->�߸���[1]; y++)
                {
                    ������.x = m���ؿ�[i]->���½�λ��.x;
                    for (int x = 0; x < m���ؿ�[i]->�߸���[0]; x++)
                    {
                        �߳�[����] = thread(���ز����߳�1, s��������, ����, m���ؿ�, ������, i, x, y, z);
                        ����++;

                        if (���� == �߳���)
                        {
                            ���� = 0;
                            for (int n = 0; n < �߳���; n++)
                                if (�߳�[n].joinable()) �߳�[n].join();
                        }

                        ������.x += ���;
                    }
                    ������.y += ���;
                }
                ������.z += ���;
            }
        }

        for (int n = 0; n < �߳���; n++)
        {
            if (�߳�[n].joinable()) �߳�[n].join();
        }
    }

    vector<bool***> �������ؿ�;
    �������ؿ�.resize(m���ؿ�.size());
    s��������->��Χ���.resize(m���ؿ�.size());

    for (int n = 0; n < m���ؿ�.size(); n++)
    {
        �������ؿ�[n] = new bool** [m���ؿ�[n]->�߸���[2]];
        for (int i = 0; i < m���ؿ�[n]->�߸���[2]; i++)
        {
            �������ؿ�[n][i] = new bool* [m���ؿ�[n]->�߸���[1]];
            for (int j = 0; j < m���ؿ�[n]->�߸���[1]; j++)
            {
                �������ؿ�[n][i][j] = new bool[m���ؿ�[n]->�߸���[0]];
                for (int k = 0; k < m���ؿ�[n]->�߸���[0]; k++)
                    �������ؿ�[n][i][j][k] = m���ؿ�[n]->����[i][j][k];
            }
        }

        vector<S����λ> ����λ��;
        bool �Ƿ��п� = 1;

        while (�Ƿ��п�)
        {
            �Ƿ��п� = 0;
            for (int z = 0; z < m���ؿ�[n]->�߸���[2]; z++)
            {
                for (int y = 0; y < m���ؿ�[n]->�߸���[1]; y++)
                {
                    for (int x = 0; x < m���ؿ�[n]->�߸���[0]; x++)
                    {
                        if (�������ؿ�[n][z][y][x])
                        {
                            UINT λ�� = ����λ��.size();
                            ����λ��.resize(����λ��.size() + 1);
                            ����λ��[λ��].x = x;
                            ����λ��[λ��].y = y;
                            ����λ��[λ��].z = z;
                            �Ƿ��п� = 1;

                            while (x - (int)����λ��[λ��].ǰ���� - 1 >= 0 && y + (int)����λ��[λ��].ǰ���� + 1 < m���ؿ�[n]->�߸���[1]
                                && z - (int)����λ��[λ��].ǰ���� - 1 >= 0)
                            {
                                if (�������ؿ�[n][z - ����λ��[λ��].ǰ���� - 1][y + ����λ��[λ��].ǰ���� + 1][x - ����λ��[λ��].ǰ���� - 1])
                                {
                                    ����λ��[λ��].ǰ����++;
                                }
                                else break;
                            }

                            while (x - (int)����λ��[λ��].ǰ���� - 1 >= 0 && y + (int)����λ��[λ��].ǰ���� + 1 < m���ؿ�[n]->�߸���[1]
                                && z + (int)����λ��[λ��].ǰ���� + 1 < m���ؿ�[n]->�߸���[2])
                            {
                                if (�������ؿ�[n][z + ����λ��[λ��].ǰ���� + 1][y + ����λ��[λ��].ǰ���� + 1][x - ����λ��[λ��].ǰ���� - 1])
                                {
                                    ����λ��[λ��].ǰ����++;
                                }
                                else break;
                            }

                            while (x - (int)����λ��[λ��].ǰ���� - 1 >= 0 && y - (int)����λ��[λ��].ǰ���� - 1 >= 0
                                && z - (int)����λ��[λ��].ǰ���� - 1 >= 0)
                            {
                                if (�������ؿ�[n][z - ����λ��[λ��].ǰ���� - 1][y - ����λ��[λ��].ǰ���� - 1][x - ����λ��[λ��].ǰ���� - 1])
                                {
                                    ����λ��[λ��].ǰ����++;
                                }
                                else break;
                            }

                            while (x - (int)����λ��[λ��].ǰ���� - 1 >= 0 && y - (int)����λ��[λ��].ǰ���� - 1 >= 0
                                && z + (int)����λ��[λ��].ǰ���� + 1 < m���ؿ�[n]->�߸���[2])
                            {
                                if (�������ؿ�[n][z + ����λ��[λ��].ǰ���� + 1][y - ����λ��[λ��].ǰ���� - 1][x - ����λ��[λ��].ǰ���� - 1])
                                {
                                    ����λ��[λ��].ǰ����++;
                                }
                                else break;
                            }

                            while (x + (int)����λ��[λ��].������ + 1 < m���ؿ�[n]->�߸���[0] && y + (int)����λ��[λ��].������ + 1 < m���ؿ�[n]->�߸���[1]
                                && z - (int)����λ��[λ��].������ - 1 >= 0)
                            {
                                if (�������ؿ�[n][z - ����λ��[λ��].������ - 1][y + ����λ��[λ��].������ + 1][x + ����λ��[λ��].������ + 1])
                                {
                                    ����λ��[λ��].������++;
                                }
                                else break;
                            }

                            while (x + (int)����λ��[λ��].������ + 1 < m���ؿ�[n]->�߸���[0] && y + (int)����λ��[λ��].������ + 1 < m���ؿ�[n]->�߸���[1]
                                && z + (int)����λ��[λ��].������ + 1 < m���ؿ�[n]->�߸���[2])
                            {
                                if (�������ؿ�[n][z + ����λ��[λ��].������ + 1][y + ����λ��[λ��].������ + 1][x + ����λ��[λ��].������ + 1])
                                {
                                    ����λ��[λ��].������++;
                                }
                                else break;
                            }

                            while (x + (int)����λ��[λ��].������ + 1 < m���ؿ�[n]->�߸���[0] && y - (int)����λ��[λ��].������ - 1 >= 0
                                && z - (int)����λ��[λ��].������ - 1 >= 0)
                            {
                                if (�������ؿ�[n][z - ����λ��[λ��].������ - 1][y - ����λ��[λ��].������ - 1][x + ����λ��[λ��].������ + 1])
                                {
                                    ����λ��[λ��].������++;
                                }
                                else break;
                            }

                            while (x + (int)����λ��[λ��].������ + 1 < m���ؿ�[n]->�߸���[0] && y - (int)����λ��[λ��].������ - 1 >= 0
                                && z + (int)����λ��[λ��].������ + 1 < m���ؿ�[n]->�߸���[2])
                            {
                                if (�������ؿ�[n][z + ����λ��[λ��].������ + 1][y - ����λ��[λ��].������ - 1][x + ����λ��[λ��].������ + 1])
                                {
                                    ����λ��[λ��].������++;
                                }
                                else break;
                            }
                        }
                    }
                }
            }

            UINT ���λ = 0;
            UINT ��С�� = 0;
            UINT ����� = 0;
            for (int i = 0; i < ����λ��.size(); i++)
            {
                UINT ��С�� = UINT32_MAX;
                if (��С�� > ����λ��[i].ǰ����) ��С�� = ����λ��[i].ǰ����;
                if (��С�� > ����λ��[i].ǰ����) ��С�� = ����λ��[i].ǰ����;
                if (��С�� > ����λ��[i].ǰ����) ��С�� = ����λ��[i].ǰ����;
                if (��С�� > ����λ��[i].ǰ����) ��С�� = ����λ��[i].ǰ����;
                if (��С�� > ����λ��[i].������) ��С�� = ����λ��[i].������;
                if (��С�� > ����λ��[i].������) ��С�� = ����λ��[i].������;
                if (��С�� > ����λ��[i].������) ��С�� = ����λ��[i].������;
                if (��С�� > ����λ��[i].������) ��С�� = ����λ��[i].������;

                if (��С�� > �����)
                {
                    ����� = ��С��;
                    ���λ = i;
                }
                else if (����� = ��С��)
                {
                    mt19937 mt(rd());
                    UINT ����� = mt() % 1;
                    if (�����) ���λ = i;
                }
            }

            if (����λ��.size() != 0)
            {
                UINT ����λ = ����λ��[���λ].ǰ����;
                UINT ���λx = ����λ��[���λ].x;
                UINT ���λy = ����λ��[���λ].y;
                UINT ���λz = ����λ��[���λ].z;

                if (����λ > ����λ��[���λ].ǰ����) ����λ = ����λ��[���λ].ǰ����;
                if (����λ > ����λ��[���λ].ǰ����) ����λ = ����λ��[���λ].ǰ����;
                if (����λ > ����λ��[���λ].ǰ����) ����λ = ����λ��[���λ].ǰ����;
                if (����λ > ����λ��[���λ].������) ����λ = ����λ��[���λ].������;
                if (����λ > ����λ��[���λ].������) ����λ = ����λ��[���λ].������;
                if (����λ > ����λ��[���λ].������) ����λ = ����λ��[���λ].������;
                if (����λ > ����λ��[���λ].������) ����λ = ����λ��[���λ].������;

                for (int k = ���λz - ����λ; k <= ���λz + ����λ; k++)
                {
                    for (int j = ���λy - ����λ; j <= ���λy + ����λ; j++)
                    {
                        for (int i = ���λx - ����λ; i <= ���λx + ����λ; i++)
                        {
                            �������ؿ�[n][k][j][i] = 0;
                        }
                    }
                }

                UINT ��ǰλ = s��������->��Χ���[n].size();
                s��������->��Χ���[n].resize(s��������->��Χ���[n].size() + 1);
                s��������->��Χ���[n][��ǰλ].����ǰλ��.x = m���ؿ�[n]->���½�λ��.x + (����λ��[���λ].x - ����λ) * m���ؿ�[n]->���;
                s��������->��Χ���[n][��ǰλ].����ǰλ��.y = m���ؿ�[n]->���½�λ��.y + (����λ��[���λ].y - ����λ) * m���ؿ�[n]->���;
                s��������->��Χ���[n][��ǰλ].����ǰλ��.z = m���ؿ�[n]->���½�λ��.z + (����λ��[���λ].z - ����λ) * m���ؿ�[n]->���;
                s��������->��Χ���[n][��ǰλ].�߳�.x = (float)(����λ * 2 + 1) * m���ؿ�[n]->���;
                s��������->��Χ���[n][��ǰλ].�߳�.y = (float)(����λ * 2 + 1) * m���ؿ�[n]->���;
                s��������->��Χ���[n][��ǰλ].�߳�.z = (float)(����λ * 2 + 1) * m���ؿ�[n]->���;
            }

            ����λ��.clear();
        }

        bool �Ƿ������� = 1;
        while (�Ƿ�������)
        {
            �Ƿ������� = 0;
            for (int i = 0; i < s��������->��Χ���[n].size(); i++)
            {
                for (int j = i; j < s��������->��Χ���[n].size(); j++)
                {
                    if (s��������->��Χ���[n][i].����ǰλ��.x == s��������->��Χ���[n][j].����ǰλ��.x && s��������->��Χ���[n][i].����ǰλ��.y == s��������->��Χ���[n][j].����ǰλ��.y
                        && s��������->��Χ���[n][i].�߳�.x == s��������->��Χ���[n][j].�߳�.x && s��������->��Χ���[n][i].�߳�.y == s��������->��Χ���[n][j].�߳�.y
                        && (s��������->��Χ���[n][i].����ǰλ��.z + s��������->��Χ���[n][i].�߳�.z == s��������->��Χ���[n][j].����ǰλ��.z
                            || s��������->��Χ���[n][j].����ǰλ��.z + s��������->��Χ���[n][j].�߳�.z == s��������->��Χ���[n][i].����ǰλ��.z))
                    {
                        �Ƿ������� = 1;
                        s��������->��Χ���[n][i].�߳�.z += s��������->��Χ���[n][j].�߳�.z;
                        if (s��������->��Χ���[n][i].����ǰλ��.z > s��������->��Χ���[n][j].����ǰλ��.z) s��������->��Χ���[n][i].����ǰλ��.z = s��������->��Χ���[n][j].����ǰλ��.z;

                        vector<S��Χ��>::iterator i��Χ�� = s��������->��Χ���[n].begin();
                        i��Χ�� += j;
                        s��������->��Χ���[n].erase(i��Χ��);

                        goto ����ѭ��;
                    }

                    if (s��������->��Χ���[n][i].����ǰλ��.x == s��������->��Χ���[n][j].����ǰλ��.x && s��������->��Χ���[n][i].����ǰλ��.z == s��������->��Χ���[n][j].����ǰλ��.z
                        && s��������->��Χ���[n][i].�߳�.x == s��������->��Χ���[n][j].�߳�.x && s��������->��Χ���[n][i].�߳�.z == s��������->��Χ���[n][j].�߳�.z
                        && (s��������->��Χ���[n][i].����ǰλ��.y + s��������->��Χ���[n][i].�߳�.y == s��������->��Χ���[n][j].����ǰλ��.y
                            || s��������->��Χ���[n][j].����ǰλ��.y + s��������->��Χ���[n][j].�߳�.y == s��������->��Χ���[n][i].����ǰλ��.y))
                    {
                        �Ƿ������� = 1;
                        s��������->��Χ���[n][i].�߳�.y += s��������->��Χ���[n][j].�߳�.y;
                        if (s��������->��Χ���[n][i].����ǰλ��.y > s��������->��Χ���[n][j].����ǰλ��.y) s��������->��Χ���[n][i].����ǰλ��.y = s��������->��Χ���[n][j].����ǰλ��.y;

                        vector<S��Χ��>::iterator i��Χ�� = s��������->��Χ���[n].begin();
                        i��Χ�� += j;
                        s��������->��Χ���[n].erase(i��Χ��);

                        goto ����ѭ��;
                    }

                    if (s��������->��Χ���[n][i].����ǰλ��.y == s��������->��Χ���[n][j].����ǰλ��.y && s��������->��Χ���[n][i].����ǰλ��.z == s��������->��Χ���[n][j].����ǰλ��.z
                        && s��������->��Χ���[n][i].�߳�.y == s��������->��Χ���[n][j].�߳�.y && s��������->��Χ���[n][i].�߳�.z == s��������->��Χ���[n][j].�߳�.z
                        && (s��������->��Χ���[n][i].����ǰλ��.x + s��������->��Χ���[n][i].�߳�.x == s��������->��Χ���[n][j].����ǰλ��.x
                            || s��������->��Χ���[n][j].����ǰλ��.x + s��������->��Χ���[n][j].�߳�.x == s��������->��Χ���[n][i].����ǰλ��.x))
                    {
                        �Ƿ������� = 1;
                        s��������->��Χ���[n][i].�߳�.x += s��������->��Χ���[n][j].�߳�.x;
                        if (s��������->��Χ���[n][i].����ǰλ��.x > s��������->��Χ���[n][j].����ǰλ��.x) s��������->��Χ���[n][i].����ǰλ��.x = s��������->��Χ���[n][j].����ǰλ��.x;

                        vector<S��Χ��>::iterator i��Χ�� = s��������->��Χ���[n].begin();
                        i��Χ�� += j;
                        s��������->��Χ���[n].erase(i��Χ��);

                        goto ����ѭ��;
                    }
                }
            }

        ����ѭ��:if (0);
        }
    }

    for (int n = 0; n < m���ؿ�.size(); n++)
    {
        for (int i = 0; i < m���ؿ�[n]->�߸���[2]; i++)
        {
            for (int j = 0; j < m���ؿ�[n]->�߸���[1]; j++)
            {
                delete[] �������ؿ�[n][i][j];
            }
            delete[] �������ؿ�[n][i];
        }
        delete[] �������ؿ�[n];
    }
    �������ؿ�.~vector();

    for(int i = 0; i < m���ؿ�.size(); i++)
        delete m���ؿ�[i];
    m���ؿ�.~vector();
}

void C��̬����::���ز����߳�(S��������* s��������, C��������* ����, vector<S���ؿ�*> m���ؿ�, XMFLOAT3 ������, UINT ���ؿ�����, UINT x, UINT y, UINT z)
{
    bool �ϲ��� = 0;
    bool �²��� = 0;
    bool ����� = 0;
    bool �Ҳ��� = 0;
    bool ǰ���� = 0;
    bool ����� = 0;
    UINT �任����;

    �任���� = 0;

    for (int i = 0; i < s��������->s����.size(); i = i + 3)
    {
        float ���� = 0;
        XMVECTOR ԭ��{};
        XMVECTOR ����{};
        XMVECTOR ����1{};
        XMVECTOR ����2{};
        XMVECTOR ����3{};

        if (����->Ԫ��[�任����]->��ʼ���� + ����->Ԫ��[�任����]->�������� <= i)
        {
            �任����++;
            �ϲ��� = 0;
            �²��� = 0;
            ����� = 0;
            �Ҳ��� = 0;
            ǰ���� = 0;
            ����� = 0;
        }
        if (�任���� != ���ؿ�����) continue;

        ԭ��.m128_f32[0] = ������.x; ԭ��.m128_f32[1] = ������.y; ԭ��.m128_f32[2] = ������.z;

        ����1.m128_f32[0] = s��������->���㼯[s��������->s����[i]].λ��.x; ����1.m128_f32[1] = s��������->���㼯[s��������->s����[i]].λ��.y;
        ����1.m128_f32[2] = s��������->���㼯[s��������->s����[i]].λ��.z;
        ����2.m128_f32[0] = s��������->���㼯[s��������->s����[i + 1]].λ��.x; ����2.m128_f32[1] = s��������->���㼯[s��������->s����[i + 1]].λ��.y;
        ����2.m128_f32[2] = s��������->���㼯[s��������->s����[i + 1]].λ��.z;
        ����3.m128_f32[0] = s��������->���㼯[s��������->s����[i + 2]].λ��.x; ����3.m128_f32[1] = s��������->���㼯[s��������->s����[i + 2]].λ��.y;
        ����3.m128_f32[2] = s��������->���㼯[s��������->s����[i + 2]].λ��.z;

        ����.m128_f32[0] = 1.0f; ����.m128_f32[1] = 0.0f; ����.m128_f32[2] = 0.0f;
        if (TriangleTests::Intersects(ԭ��, ����, ����1, ����2, ����3, ����)) ����� = 1;
        ����.m128_f32[0] = -1.0f; ����.m128_f32[1] = 0.0f; ����.m128_f32[2] = 0.0f;
        if (TriangleTests::Intersects(ԭ��, ����, ����1, ����2, ����3, ����)) ǰ���� = 1;
        ����.m128_f32[0] = 0.0f; ����.m128_f32[1] = 1.0f; ����.m128_f32[2] = 0.0f;
        if (TriangleTests::Intersects(ԭ��, ����, ����1, ����2, ����3, ����)) �ϲ��� = 1;
        ����.m128_f32[0] = 0.0f; ����.m128_f32[1] = -1.0f; ����.m128_f32[2] = 0.0f;
        if (TriangleTests::Intersects(ԭ��, ����, ����1, ����2, ����3, ����)) �²��� = 1;
        ����.m128_f32[0] = 0.0f; ����.m128_f32[1] = 0.0f; ����.m128_f32[2] = 1.0f;
        if (TriangleTests::Intersects(ԭ��, ����, ����1, ����2, ����3, ����)) �Ҳ��� = 1;
        ����.m128_f32[0] = 0.0f; ����.m128_f32[1] = 0.0f; ����.m128_f32[2] = -1.0f;
        if (TriangleTests::Intersects(ԭ��, ����, ����1, ����2, ����3, ����)) ����� = 1;

        if (�ϲ��� && �²��� && ����� && �Ҳ��� && ǰ���� && �����)
        {
            m���ؿ�[���ؿ�����]->����[z][y][x] = 1;
        }
    }
}

void C��̬����::���ز����߳�1(S��������* s��������, C��������* ����, vector<S���ؿ�*> m���ؿ�, XMFLOAT3 ������, UINT ���ؿ�����, UINT x, UINT y, UINT z)
{
    bool �ϲ��� = 0;
    bool �²��� = 0;
    bool ����� = 0;
    bool �Ҳ��� = 0;
    bool ǰ���� = 0;
    bool ����� = 0;
    UINT �任���� = 0;

    for (int i = 0; i < s��������->����.size(); i = i + 3)
    {
        float ���� = 0;
        XMVECTOR ԭ��{};
        XMVECTOR ����{};
        XMVECTOR ����1{};
        XMVECTOR ����2{};
        XMVECTOR ����3{};

        if (����->Ԫ��[�任����]->��ʼ���� + ����->Ԫ��[�任����]->�������� <= i)
        {
            �任����++;
            �ϲ��� = 0;
            �²��� = 0;
            ����� = 0;
            �Ҳ��� = 0;
            ǰ���� = 0;
            ����� = 0;
        }
        if (�任���� != ���ؿ�����) continue;

        ԭ��.m128_f32[0] = ������.x; ԭ��.m128_f32[1] = ������.y; ԭ��.m128_f32[2] = ������.z;

        ����1.m128_f32[0] = s��������->���㼯[s��������->����[i]].λ��.x; ����1.m128_f32[1] = s��������->���㼯[s��������->����[i]].λ��.y;
        ����1.m128_f32[2] = s��������->���㼯[s��������->����[i]].λ��.z;
        ����2.m128_f32[0] = s��������->���㼯[s��������->����[i + 1]].λ��.x; ����2.m128_f32[1] = s��������->���㼯[s��������->����[i + 1]].λ��.y;
        ����2.m128_f32[2] = s��������->���㼯[s��������->����[i + 1]].λ��.z;
        ����3.m128_f32[0] = s��������->���㼯[s��������->����[i + 2]].λ��.x; ����3.m128_f32[1] = s��������->���㼯[s��������->����[i + 2]].λ��.y;
        ����3.m128_f32[2] = s��������->���㼯[s��������->����[i + 2]].λ��.z;

        ����.m128_f32[0] = 1.0f; ����.m128_f32[1] = 0.0f; ����.m128_f32[2] = 0.0f;
        if (TriangleTests::Intersects(ԭ��, ����, ����1, ����2, ����3, ����)) ����� = 1;
        ����.m128_f32[0] = -1.0f; ����.m128_f32[1] = 0.0f; ����.m128_f32[2] = 0.0f;
        if (TriangleTests::Intersects(ԭ��, ����, ����1, ����2, ����3, ����)) ǰ���� = 1;
        ����.m128_f32[0] = 0.0f; ����.m128_f32[1] = 1.0f; ����.m128_f32[2] = 0.0f;
        if (TriangleTests::Intersects(ԭ��, ����, ����1, ����2, ����3, ����)) �ϲ��� = 1;
        ����.m128_f32[0] = 0.0f; ����.m128_f32[1] = -1.0f; ����.m128_f32[2] = 0.0f;
        if (TriangleTests::Intersects(ԭ��, ����, ����1, ����2, ����3, ����)) �²��� = 1;
        ����.m128_f32[0] = 0.0f; ����.m128_f32[1] = 0.0f; ����.m128_f32[2] = 1.0f;
        if (TriangleTests::Intersects(ԭ��, ����, ����1, ����2, ����3, ����)) �Ҳ��� = 1;
        ����.m128_f32[0] = 0.0f; ����.m128_f32[1] = 0.0f; ����.m128_f32[2] = -1.0f;
        if (TriangleTests::Intersects(ԭ��, ����, ����1, ����2, ����3, ����)) ����� = 1;

        if (�ϲ��� && �²��� && ����� && �Ҳ��� && ǰ���� && �����)
        {
            m���ؿ�[���ؿ�����]->����[z][y][x] = 1;
        }
    }
}

void C��̬����::������Χ�򻺴�()
{
    for (int i = 0; i <����->Ԫ��.size(); i++)
    {
        if (s��������->��Χ���[i].size() != 0)
        {
            D3D12_HEAP_PROPERTIES HeapProperties = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT);
            D3D12_RESOURCE_DESC Desc = CD3DX12_RESOURCE_DESC::Buffer(sizeof(C��̬����::S��Χ��) * s��������->��Χ���[i].size());
            �豸->CreateCommittedResource(
                &HeapProperties,
                D3D12_HEAP_FLAG_NONE,
                &Desc,
                D3D12_RESOURCE_STATE_COMMON,
                nullptr,
                IID_PPV_ARGS(&����->Ԫ��[i]->��Χ��));

            HeapProperties = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
            Desc = CD3DX12_RESOURCE_DESC::Buffer(sizeof(C��̬����::S��Χ��) * s��������->��Χ���[i].size());
            �豸->CreateCommittedResource(
                &HeapProperties,
                D3D12_HEAP_FLAG_NONE,
                &Desc,
                D3D12_RESOURCE_STATE_GENERIC_READ,
                nullptr,
                IID_PPV_ARGS(&����->Ԫ��[i]->��Χ���ϴ�));

            D3D12_SUBRESOURCE_DATA subResourceData = {};
            subResourceData.pData = s��������->��Χ���[i].data();
            subResourceData.RowPitch = sizeof(C��̬����::S��Χ��) * s��������->��Χ���[i].size();
            subResourceData.SlicePitch = subResourceData.RowPitch;

            D3D12_RESOURCE_BARRIER pBarriers = CD3DX12_RESOURCE_BARRIER::Transition(����->Ԫ��[i]->��Χ��.Get(),
                D3D12_RESOURCE_STATE_COMMON, D3D12_RESOURCE_STATE_COPY_DEST);
            �������->ResourceBarrier(1, &pBarriers);
            UpdateSubresources<1>(�������.Get(), ����->Ԫ��[i]->��Χ��.Get(), ����->Ԫ��[i]->��Χ���ϴ�.Get(), 0, 0, 1, &subResourceData);
            pBarriers = CD3DX12_RESOURCE_BARRIER::Transition(����->Ԫ��[i]->��Χ��.Get(),
                D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_GENERIC_READ);
            �������->ResourceBarrier(1, &pBarriers);

            D3D12_SHADER_RESOURCE_VIEW_DESC* srvDesc = new D3D12_SHADER_RESOURCE_VIEW_DESC;
            srvDesc->Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
            srvDesc->Format = DXGI_FORMAT_UNKNOWN;
            srvDesc->ViewDimension = D3D12_SRV_DIMENSION_BUFFER;
            srvDesc->Buffer.Flags = D3D12_BUFFER_SRV_FLAG_NONE;
            srvDesc->Buffer.NumElements = s��������->��Χ���[i].size();
            srvDesc->Buffer.StructureByteStride = sizeof(C��̬����::S��Χ��);
            srvDesc->Buffer.FirstElement = 0;

            �������ѹ���->����srv������(����->Ԫ��[i]->��Χ��, �������Ƽ� + L"." + ����->Ԫ��[i]->�������� + L"��Χ��srv", srvDesc);
        }

        D3D12_HEAP_PROPERTIES HeapProperties = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT);
        D3D12_RESOURCE_DESC Desc = CD3DX12_RESOURCE_DESC::Buffer(sizeof(Sʰȡ���),
            D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS);
        �豸->CreateCommittedResource(
            &HeapProperties,
            D3D12_HEAP_FLAG_NONE,
            &Desc,
            D3D12_RESOURCE_STATE_COMMON,
            nullptr,
            IID_PPV_ARGS(&����->Ԫ��[i]->ʰȡ���));

        HeapProperties = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
        Desc = CD3DX12_RESOURCE_DESC::Buffer(sizeof(Sʰȡ���));
        �豸->CreateCommittedResource(
            &HeapProperties,
            D3D12_HEAP_FLAG_NONE,
            &Desc,
            D3D12_RESOURCE_STATE_GENERIC_READ,
            nullptr,
            IID_PPV_ARGS(&����->Ԫ��[i]->ʰȡ����ϴ�));

        Sʰȡ��� data{};
        D3D12_SUBRESOURCE_DATA subResourceData = {};
        subResourceData.pData = &data;
        subResourceData.RowPitch = sizeof(Sʰȡ���);
        subResourceData.SlicePitch = subResourceData.RowPitch;

        D3D12_RESOURCE_BARRIER pBarriers = CD3DX12_RESOURCE_BARRIER::Transition(����->Ԫ��[i]->ʰȡ���.Get(),
            D3D12_RESOURCE_STATE_COMMON, D3D12_RESOURCE_STATE_COPY_DEST);
        �������->ResourceBarrier(1, &pBarriers);
        UpdateSubresources<1>(�������.Get(), ����->Ԫ��[i]->ʰȡ���.Get(), ����->Ԫ��[i]->ʰȡ����ϴ�.Get(), 0, 0, 1, &subResourceData);
        pBarriers = CD3DX12_RESOURCE_BARRIER::Transition(����->Ԫ��[i]->ʰȡ���.Get(),
            D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_UNORDERED_ACCESS);
        �������->ResourceBarrier(1, &pBarriers);

        D3D12_UNORDERED_ACCESS_VIEW_DESC* uavDesc = new D3D12_UNORDERED_ACCESS_VIEW_DESC;
        uavDesc->Format = DXGI_FORMAT_UNKNOWN;
        uavDesc->ViewDimension = D3D12_UAV_DIMENSION_BUFFER;
        uavDesc->Buffer.Flags = D3D12_BUFFER_UAV_FLAG_NONE;
        uavDesc->Buffer.NumElements = 1;
        uavDesc->Buffer.StructureByteStride = sizeof(Sʰȡ���);
        uavDesc->Buffer.FirstElement = 0;
        uavDesc->Buffer.CounterOffsetInBytes = 0;

        �������ѹ���->����uav������(����->Ԫ��[i]->ʰȡ���, �������Ƽ� + L"." + ����->Ԫ��[i]->�������� + L"ʰȡ���uav", uavDesc);
    }

    for (int i = 0; i < s��������->��Χ���.size(); i++)
    {
        ����->Ԫ��[i]->��Χ������ = s��������->��Χ���[i].size();
    }
}

void C��̬����::��������������()
{
    D3D12_SHADER_RESOURCE_VIEW_DESC* srvDesc;

    for (int i = 0; i < ����->Ԫ��.size(); i++)
    {
        srvDesc = new D3D12_SHADER_RESOURCE_VIEW_DESC;
        srvDesc->Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
        srvDesc->Format = ����->����[����->Ԫ��[i]->��������]->GetDesc().Format;
        srvDesc->ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
        srvDesc->Texture2D.MipLevels = ����->����[����->Ԫ��[i]->��������]->GetDesc().MipLevels;
        srvDesc->Texture2D.MostDetailedMip = 0;
        srvDesc->Texture2D.ResourceMinLODClamp = 0.0f;
        srvDesc->Texture2D.PlaneSlice = 0;

        �������ѹ���->����srv������(����->����[����->Ԫ��[i]->��������], �������Ƽ� + L"." + ����->Ԫ��[i]->�������� + L"����srv", srvDesc);
    }
}

void C��̬����::������Χ��()
{
    XMVECTOR ���ĵ�{};
    XMVECTOR ��ǰ��{};
    float ��Զ���� = 0;
    bool ��ʼ�� = 0;

    for (int i = 0; i < ����->Ԫ��.size(); i++)
    {
        if (������ʽ == DXGI_FORMAT_R32_UINT)
        {
            for (int j = ����->Ԫ��[i]->��ʼ����; j < ����->Ԫ��[i]->��ʼ���� + ����->Ԫ��[i]->��������; j++)
            {
                ���ĵ�.m128_f32[0] += s��������->���㼯[s��������->����[j]].λ��.x; ���ĵ�.m128_f32[1] += s��������->���㼯[s��������->����[j]].λ��.y;
                ���ĵ�.m128_f32[2] += s��������->���㼯[s��������->����[j]].λ��.z;
                if (��ʼ��)
                {
                    ���ĵ� /= 2;
                }
                ��ʼ�� = 1;
            }

            for (int j = ����->Ԫ��[i]->��ʼ����; j < ����->Ԫ��[i]->��ʼ���� + ����->Ԫ��[i]->��������; j++)
            {
                ��ǰ��.m128_f32[0] = s��������->���㼯[s��������->����[j]].λ��.x; ��ǰ��.m128_f32[1] = s��������->���㼯[s��������->����[j]].λ��.y;
                ��ǰ��.m128_f32[2] = s��������->���㼯[s��������->����[j]].λ��.z;
                if (XMVector3Length(��ǰ�� - ���ĵ�).m128_f32[0] > ��Զ����)
                {
                    ��Զ���� = XMVector3Length(��ǰ�� - ���ĵ�).m128_f32[0];
                }
            }

            ����->Ԫ��[i]->��Χ��.Center.x = ���ĵ�.m128_f32[0]; ����->Ԫ��[i]->��Χ��.Center.y = ���ĵ�.m128_f32[1];
            ����->Ԫ��[i]->��Χ��.Center.z = ���ĵ�.m128_f32[2];
            ����->Ԫ��[i]->��Χ��.Radius = ��Զ����;
        }
        else if (������ʽ == DXGI_FORMAT_R16_UINT)
        {
            for (int j = ����->Ԫ��[i]->��ʼ����; j < ����->Ԫ��[i]->��ʼ���� + ����->Ԫ��[i]->��������; j++)
            {
                ���ĵ�.m128_f32[0] += s��������->���㼯[s��������->s����[j]].λ��.x; ���ĵ�.m128_f32[1] += s��������->���㼯[s��������->s����[j]].λ��.y;
                ���ĵ�.m128_f32[2] += s��������->���㼯[s��������->s����[j]].λ��.z;
                if (��ʼ��)
                {
                    ���ĵ� /= 2;
                }
                ��ʼ�� = 1;
            }

            for (int j = ����->Ԫ��[i]->��ʼ����; j < ����->Ԫ��[i]->��ʼ���� + ����->Ԫ��[i]->��������; j++)
            {
                ��ǰ��.m128_f32[0] = s��������->���㼯[s��������->s����[j]].λ��.x; ��ǰ��.m128_f32[1] = s��������->���㼯[s��������->s����[j]].λ��.y;
                ��ǰ��.m128_f32[2] = s��������->���㼯[s��������->s����[j]].λ��.z;
                if (XMVector3Length(��ǰ�� - ���ĵ�).m128_f32[0] > ��Զ����)
                {
                    ��Զ���� = XMVector3Length(��ǰ�� - ���ĵ�).m128_f32[0];
                }
            }

            ����->Ԫ��[i]->��Χ��.Center.x = ���ĵ�.m128_f32[0]; ����->Ԫ��[i]->��Χ��.Center.y = ���ĵ�.m128_f32[1];
            ����->Ԫ��[i]->��Χ��.Center.z = ���ĵ�.m128_f32[2];
            ����->Ԫ��[i]->��Χ��.Radius = ��Զ����;
        }
    }
}

void C��̬����::��������(UINT ����)
{
    �������->IASetVertexBuffers(0, 1, &vbv);
    �������->IASetIndexBuffer(&ibv);
    �������->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    �������->DrawIndexedInstanced(this->����->Ԫ��[����]->��������, 1, this->����->Ԫ��[����]->��ʼ����, 0, 0);
}

void C��̬����::�ͷźϲ���Ϣ()
{
    m�ϲ�������.~vector();
    m���ƶ��㼯.~vector();
}

C��̬����::~C��̬����()
{
    delete ����;
    delete s��������;
}