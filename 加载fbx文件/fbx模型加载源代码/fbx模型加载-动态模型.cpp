#include"fbxģ�ͼ���-��̬ģ��.h"

C��̬����::C��̬����(ComPtr<ID3D12Device> �豸, ComPtr<ID3D12GraphicsCommandList> �������, C�������ѹ���* �������ѹ���, C������Դ* ������Դ)
{
    this->�豸 = �豸;
    this->������� = �������;
    this->������Դ = ������Դ;
    this->�������ѹ��� = �������ѹ���;
}

//����mdd�ļ�-------------------------------------------------------------------
void C��̬����::����mdd�ļ�(wstring �ļ�����)
{
    ofstream ����ļ�;
    string �ļ�����;
    string ͼƬ����;
    string ͼƬ����3;
    wstring �ļ�����·��;
    WCHAR ͼƬ����w[128]{};
    char ͼƬ����1[128]{};
    string ͼƬ����2;
    UINT �ַ������� = 0;
    UINT i = 0;
    UINT j = 0;
    UINT k = 0;

    for (int i = 0; i < �ļ�����.size(); i++)
    {
        if (�ļ�����[i] == '.') break;
        �ļ�����·�� += �ļ�����[i];
    }

    if (CreateDirectory(�ļ�����·��.c_str(), 0) == 0)
    {
        wstring bug = L"�ļ����� line:" + to_wstring(__LINE__);
        bug += L"\n";
        OutputDebugString(bug.c_str());
    }

    WideCharToMultiByte(CP_ACP, 0, �ļ�����·��.c_str(), �ļ�����·��.size(), ͼƬ����1, 128, 0, 0);
    �ļ����� = �ļ�����·�� + L"\\" + �ļ�����;

    ����ļ�.open(�ļ�����);

    if (!����ļ�.is_open())
    {
        wstring bug = L"�ļ��޷��� line:" + to_wstring(__LINE__);
        bug += L"\n";
        OutputDebugString(bug.c_str());
        PostQuitMessage(0);
        return;
    }

    �ļ����� = "����������" + to_string(����->Ԫ��.size()) + "��\n";
    ����ļ�.write(�ļ�����.c_str(), �ļ�����.size());

    for (i = 0; i < s��������->·����.size(); i++)
    {
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

        ͼƬ����2 = ͼƬ����;
        ͼƬ����3 = ͼƬ����1; 
        ͼƬ���� = ͼƬ����3 + "\\" + ͼƬ����;

        int ���� = MultiByteToWideChar(CP_ACP, 0, ͼƬ����.c_str(), ͼƬ����.size(), ͼƬ����w, 128);
        ͼƬ����w[����] = 0;

        CopyFile(s��������->·����[i].c_str(), ͼƬ����w, TRUE);

        �ļ����� = "�������ƣ�" + ͼƬ����2 + "��\n";
        ����ļ�.write(�ļ�����.c_str(), �ļ�����.size());
    }

    �ļ����� = "\n";
    ����ļ�.write(�ļ�����.c_str(), �ļ�����.size());

    for (i = 0; i < ����->Ԫ��.size(); i++)
    {
        char ��������[128]{};
        int ���� = WideCharToMultiByte(CP_ACP, 0, ����->Ԫ��[i]->��������.c_str(), ����->Ԫ��[i]->��������.size(), ��������, 128, 0, 0);
        ��������[����] = 0;

        �ļ����� = "��������.�������ƣ�"; �ļ����� += ��������; �ļ����� += "��\n";
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
        �ļ����� = "����.λ�ã�" + to_string(s��������->���㼯[i].λ��.x) + "��" +
            to_string(s��������->���㼯[i].λ��.y) + "��" + to_string(s��������->���㼯[i].λ��.z) + "��\n";
        ����ļ�.write(�ļ�����.c_str(), �ļ�����.size());

        �ļ����� = "����.��������" + to_string(s��������->���㼯[i].������.x) + "��" +
            to_string(s��������->���㼯[i].������.y) + "��" + to_string(s��������->���㼯[i].������.z) + "��\n";
        ����ļ�.write(�ļ�����.c_str(), �ļ�����.size());

        �ļ����� = "����.����" + to_string(s��������->���㼯[i].��������.x) + "��" +
            to_string(s��������->���㼯[i].��������.y) + "��\n";
        ����ļ�.write(�ļ�����.c_str(), �ļ�����.size());

        �ļ����� = "����.��������������" + to_string(s��������->���㼯[i].������������[0]) + "��" +
            to_string(s��������->���㼯[i].������������[1]) + "��" + to_string(s��������->���㼯[i].������������[2]) 
            + "��" + to_string(s��������->���㼯[i].������������[2]) + "��\n";
        ����ļ�.write(�ļ�����.c_str(), �ļ�����.size());

        �ļ����� = "����.����Ȩ�أ�" + to_string(s��������->���㼯[i].����Ȩ��[0]) + "��" +
            to_string(s��������->���㼯[i].����Ȩ��[1]) + "��" + to_string(s��������->���㼯[i].����Ȩ��[2]) + "��\n";
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

    �ļ����� = "\n���������" + to_string(�������.size()) + "��\n";
    ����ļ�.write(�ļ�����.c_str(), �ļ�����.size());

    �ļ����� = "����������" + to_string(��������) + "��\n";
    ����ļ�.write(�ļ�����.c_str(), �ļ�����.size());

    for (i = 0; i < �������.size(); i++)
    {
        char �������[128]{};
        int ���� = WideCharToMultiByte(CP_ACP, 0, �������[i].�������.c_str(), �������[i].�������.size(), �������, 128, 0, 0);
        �������[����] = 0;

        �ļ����� = "�������.������ƣ�"; �ļ����� += �������; �ļ����� += "��\n";
        ����ļ�.write(�ļ�����.c_str(), �ļ�����.size());

        �ļ����� = "�������.ԭʼʱ����" + to_string(�������[i].ԭʼʱ��) + "��\n";
        ����ļ�.write(�ļ�����.c_str(), �ļ�����.size());

        �ļ����� = "�������.��֡����" + to_string(�������[i].֡.size()) + "��\n";
        ����ļ�.write(�ļ�����.c_str(), �ļ�����.size());
        
        for (j = 0; j < �������[i].֡.size(); j++)
        {
            �ļ����� = "�������.����������" + to_string(�������[i].֡[j].����任.size()) + "��\n";
            ����ļ�.write(�ļ�����.c_str(), �ļ�����.size());

            for (k = 0; k < �������[i].֡[j].����任.size(); k++)
            {
                �ļ����� = "�������.����任.�任��" + to_string(�������[i].֡[j].����任[k].m[0][0]) + "��"
                    + to_string(�������[i].֡[j].����任[k].m[0][1]) + "��" + to_string(�������[i].֡[j].����任[k].m[0][2]) + "��"
                    + to_string(�������[i].֡[j].����任[k].m[1][0]) + "��" + to_string(�������[i].֡[j].����任[k].m[1][1]) + "��"
                    + to_string(�������[i].֡[j].����任[k].m[1][2]) + "��" + to_string(�������[i].֡[j].����任[k].m[2][0]) + "��"
                    + to_string(�������[i].֡[j].����任[k].m[2][1]) + "��" + to_string(�������[i].֡[j].����任[k].m[2][2]) + "��"
                    + to_string(�������[i].֡[j].����任[k].m[3][0]) + "��" + to_string(�������[i].֡[j].����任[k].m[3][1]) + "��"
                    + to_string(�������[i].֡[j].����任[k].m[3][2]) + "��\n";
                ����ļ�.write(�ļ�����.c_str(), �ļ�����.size());
            }

            �ļ����� = "\n";
            ����ļ�.write(�ļ�����.c_str(), �ļ�����.size());

            �ļ����� = "�������.����������" + to_string(�������[i].֡[j].�����任.size()) + "��\n";
            ����ļ�.write(�ļ�����.c_str(), �ļ�����.size());

            for (k = 0; k < �������[i].֡[j].�����任.size(); k++)
            {
                �ļ����� = "�������.�����任.�任��" + to_string(�������[i].֡[j].�����任[k].m[0][0]) + "��"
                    + to_string(�������[i].֡[j].�����任[k].m[0][1]) + "��" + to_string(�������[i].֡[j].�����任[k].m[0][2]) + "��"
                    + to_string(�������[i].֡[j].�����任[k].m[1][0]) + "��" + to_string(�������[i].֡[j].�����任[k].m[1][1]) + "��"
                    + to_string(�������[i].֡[j].�����任[k].m[1][2]) + "��" + to_string(�������[i].֡[j].�����任[k].m[2][0]) + "��"
                    + to_string(�������[i].֡[j].�����任[k].m[2][1]) + "��" + to_string(�������[i].֡[j].�����任[k].m[2][2]) + "��"
                    + to_string(�������[i].֡[j].�����任[k].m[3][0]) + "��" + to_string(�������[i].֡[j].�����任[k].m[3][1]) + "��"
                    + to_string(�������[i].֡[j].�����任[k].m[3][2]) + "��\n";
                ����ļ�.write(�ļ�����.c_str(), �ļ�����.size());
            }

            �ļ����� = "\n";
            ����ļ�.write(�ļ�����.c_str(), �ļ�����.size());
        }
    }

    �ļ����� = "\n";
    ����ļ�.write(�ļ�����.c_str(), �ļ�����.size());

    ����ļ�.close();
}

//mdd�ļ�����---------------------------------------------------------------------

void C��̬����::����mdd�ļ�(wstring �ļ�����, wstring �������Ƽ�)
{
    ifstream �����ļ�;
    map<wstring, int> id;
    wstring �ؼ��� = L"";
    wstring ��ֵ[20];
    UINT ���� = 0;
    UINT i = 0;
    UINT j = 0;
    char ��ֵ2[128];
    char ����[256];
    WCHAR ����2[256];
    UINT �ַ������� = 0;
    UINT ���Բ��� = 0;
    UINT ���㲽�� = 0;
    UINT �������� = 0;
    wstring ����·��;
    WCHAR ����·��w[128]{};
    WCHAR ͼƬ����[128]{};
    UINT ������� = 0;
    UINT ֡���� = 0;
    UINT ����任���� = 0;
    UINT �����任���� = 0;
    int ���� = 0;
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
    id.insert(pair<wstring, int>(L"�������", 23));
    id.insert(pair<wstring, int>(L"��������", 24));
    id.insert(pair<wstring, int>(L"�������.�������", 25));
    id.insert(pair<wstring, int>(L"�������.ԭʼʱ��", 26));
    id.insert(pair<wstring, int>(L"�������.��֡��", 27));
    id.insert(pair<wstring, int>(L"�������.��������", 28));
    id.insert(pair<wstring, int>(L"�������.����任.�任", 29));
    id.insert(pair<wstring, int>(L"�������.��������", 30));
    id.insert(pair<wstring, int>(L"�������.�����任.�任", 31));
    id.insert(pair<wstring, int>(L"����.������������", 32));
    id.insert(pair<wstring, int>(L"����.����Ȩ��", 33));

    �����ļ�.open(�ļ�����);

    if (!�����ļ�.is_open())
    {
        wstring bug = L"�ļ��޷��� line:" + to_wstring(__LINE__);
        bug += L"\n";
        OutputDebugString(bug.c_str());
        PostQuitMessage(0);
        return;
    }

    s�������� = new S��������;

    while (!�����ļ�.eof())
    {
        �ؼ���.clear();
        for (i = 0; i < ����; i++)
            ��ֵ[i].clear();
        ���� = 0;

        �����ļ�.getline(����, 256);
        �ַ������� = MultiByteToWideChar(CP_ACP, 0, ����, strlen(����), ����2, 256);
        ����2[�ַ�������] = 0;

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

        if (�ؼ���[0] != '\0')
        switch (id[�ؼ���])
        {
        case 0:
            ���� = new C��������;
            ����->Ԫ��.resize(stoi(��ֵ[0]));
            for (int i = 0; i < ����->Ԫ��.size(); i++)
            {
                ����->Ԫ��[i] = new C��������::S����;
            }
            ����->����.resize(1);
            ����->����[0] = ������Դ->����ͼ;
            ����->�����ϴ�.resize(1);
            ����->�����ϴ�[0] = nullptr;
            break;

        case 1:
            ����->Ԫ��[���Բ���]->�������� = ��ֵ[0].c_str();
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
            ����->Ԫ��[���Բ���]->����.������.z = stof(��ֵ[2]);
            break;

        case 8:
            ����->Ԫ��[���Բ���]->����.�Է���.x = stof(��ֵ[0]); ����->Ԫ��[���Բ���]->����.�Է���.y = stof(��ֵ[1]);
            ����->Ԫ��[���Բ���]->����.�Է���.z = stof(��ֵ[2]);
            break;

        case 9:
            ����->Ԫ��[���Բ���]->����.������.x = stof(��ֵ[0]); ����->Ԫ��[���Բ���]->����.������.y = stof(��ֵ[1]);
            ����->Ԫ��[���Բ���]->����.������.z = stof(��ֵ[2]);
            break;

        case 10:
            ����->Ԫ��[���Բ���]->����.����� = stoi(��ֵ[0]);
            break;

        case 11:
            ����->Ԫ��[���Բ���]->����.�߹⼶�� = stoi(��ֵ[0]);
            break;

        case 12:
            ����->Ԫ��[���Բ���]->����.��͸���� = stoi(��ֵ[0]);
            ���Բ���++;
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
            break;

        case 32:
            s��������->���㼯[���㲽��].������������[0] = stof(��ֵ[0]); s��������->���㼯[���㲽��].������������[1] = stof(��ֵ[1]);
            s��������->���㼯[���㲽��].������������[2] = stof(��ֵ[2]); s��������->���㼯[���㲽��].������������[3] = stof(��ֵ[3]);
            break;

        case 33:
            s��������->���㼯[���㲽��].����Ȩ��[0] = stof(��ֵ[0]); s��������->���㼯[���㲽��].����Ȩ��[1] = stof(��ֵ[1]);
            s��������->���㼯[���㲽��].����Ȩ��[2] = stof(��ֵ[2]);
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
            for(int i = 0; i < �ļ�����.size(); i++)
                ͼƬ����[i] = �ļ�����[i];
            ͼƬ����[i] = L'\0';

            i = �ļ�����.size();
            while (1)
            {
                if (ͼƬ����[i] == L'/')
                {
                    ͼƬ����[i] = L'\0';
                    break;
                }
                else if (ͼƬ����[i] == L'\\')
                {
                    ͼƬ����[i] = L'\0';
                    break;
                }
                i--;
            }
            ����·�� = ͼƬ����;

            ����·�� += L"\\";
            ����·�� += ��ֵ[0].c_str();

            for (i = 0; i < s��������->·����.size(); i++)
            {
                if (����·�� == s��������->·����[i])
                {
                    goto ����;
                }
            }
            s��������->·����.push_back(����·��);

            �ļ�����.clear();
            �Ƿ���¼ = 0;
            for (int i = 0; i < ����·��.size(); i++)
            {
                if (�Ƿ���¼) �ļ����� += ����·��[i];
                if (����·��[i] == '.')
                {
                    �Ƿ���¼ = 1;
                    �ļ�����.clear();
                }
            }

            ����->����.resize(����->����.size() + 1);
            ����->�����ϴ�.resize(����->�����ϴ�.size() + 1);
            if (�ļ����� == L"dds")
            {
                if (!SUCCEEDED(CreateDDSTextureFromFile12(�豸.Get(), �������.Get(), ����·��.c_str(), this->����->����[this->����->����.size() - 1],
                    this->����->�����ϴ�[this->����->�����ϴ�.size() - 1])))
                {
                    wstring bug = L"����mdd�ļ�ʱ�Ҳ�����ͼ line:" + to_wstring(__LINE__);
                    bug += L"\n";
                    OutputDebugString(bug.c_str());
                    PostQuitMessage(0);
                    return;
                }
            }
            else
            {
                if (!SUCCEEDED(CreateImageDataTextureFromFile(�豸.Get(), �������.Get(), ����·��.c_str(), this->����->����[this->����->����.size() - 1],
                    this->����->�����ϴ�[this->����->�����ϴ�.size() - 1])))
                {
                    wstring bug = L"����ģ�Ͳ���ʱδ�ҵ���ͼ�ļ� line:";
                    bug += to_wstring(__LINE__) + L"\n";
                    OutputDebugString(bug.c_str());
                    PostQuitMessage(0);
                    return;
                }
            }

        ����:
            break;

        case 23:
            �������.resize(stoi(��ֵ[0]));
            break;

        case 24:
            �������� = stoi(��ֵ[0]);
            break;

        case 25:
            ֡���� = 0;
            �������[�������].������� = ��ֵ[0].c_str();
            �������++;
            break;

        case 26:
            �������[������� - 1].ԭʼʱ�� = stof(��ֵ[0]);
            break;

        case 27:
            �������[������� - 1].֡.resize(stoi(��ֵ[0]));
            break;

        case 28:
            ����任���� = 0;
            �������[������� - 1].֡[֡����].����任.resize(stoi(��ֵ[0]));
            break;
        
        case 29:
            �������[������� - 1].֡[֡����].����任[����任����].m[0][0] = stof(��ֵ[0]);
            �������[������� - 1].֡[֡����].����任[����任����].m[0][1] = stof(��ֵ[1]);
            �������[������� - 1].֡[֡����].����任[����任����].m[0][2] = stof(��ֵ[2]);
            �������[������� - 1].֡[֡����].����任[����任����].m[1][0] = stof(��ֵ[3]);
            �������[������� - 1].֡[֡����].����任[����任����].m[1][1] = stof(��ֵ[4]);
            �������[������� - 1].֡[֡����].����任[����任����].m[1][2] = stof(��ֵ[5]);
            �������[������� - 1].֡[֡����].����任[����任����].m[2][0] = stof(��ֵ[6]);
            �������[������� - 1].֡[֡����].����任[����任����].m[2][1] = stof(��ֵ[7]);
            �������[������� - 1].֡[֡����].����任[����任����].m[2][2] = stof(��ֵ[8]);
            �������[������� - 1].֡[֡����].����任[����任����].m[3][0] = stof(��ֵ[9]);
            �������[������� - 1].֡[֡����].����任[����任����].m[3][1] = stof(��ֵ[10]);
            �������[������� - 1].֡[֡����].����任[����任����].m[3][2] = stof(��ֵ[11]);
            ����任����++;
            break;

        case 30:
            �����任���� = 0;
            �������[������� - 1].֡[֡����].�����任.resize(stoi(��ֵ[0]));
            ֡����++;
            break;

        case 31:
            �������[������� - 1].֡[֡���� - 1].�����任[�����任����].m[0][0] = stof(��ֵ[0]);
            �������[������� - 1].֡[֡���� - 1].�����任[�����任����].m[0][1] = stof(��ֵ[1]);
            �������[������� - 1].֡[֡���� - 1].�����任[�����任����].m[0][2] = stof(��ֵ[2]);
            �������[������� - 1].֡[֡���� - 1].�����任[�����任����].m[1][0] = stof(��ֵ[3]);
            �������[������� - 1].֡[֡���� - 1].�����任[�����任����].m[1][1] = stof(��ֵ[4]);
            �������[������� - 1].֡[֡���� - 1].�����任[�����任����].m[1][2] = stof(��ֵ[5]);
            �������[������� - 1].֡[֡���� - 1].�����任[�����任����].m[2][0] = stof(��ֵ[6]);
            �������[������� - 1].֡[֡���� - 1].�����任[�����任����].m[2][1] = stof(��ֵ[7]);
            �������[������� - 1].֡[֡���� - 1].�����任[�����任����].m[2][2] = stof(��ֵ[8]);
            �������[������� - 1].֡[֡���� - 1].�����任[�����任����].m[3][0] = stof(��ֵ[9]);
            �������[������� - 1].֡[֡���� - 1].�����任[�����任����].m[3][1] = stof(��ֵ[10]);
            �������[������� - 1].֡[֡���� - 1].�����任[�����任����].m[3][2] = stof(��ֵ[11]);
            �����任����++;
            break;

        default:
            break;
        }
    }

    �����ļ�.close();

    ���㵥Ԫ��С = sizeof(S����);
    ���㲼�� = FVFλ�� | FVF������ | FVF�������� | FVFȨ�� | FVF��������;

    s�����任 = new XMMATRIX[��������];
    for (int i = 0; i < ��������; i++)
        s�����任[i] = XMMatrixIdentity();

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
    else if (������ʽ == DXGI_FORMAT_R32_UINT)
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

    ��������������();
}

//��̬����----------------------------------------------------------------------
void C��̬����::����FBX�ļ�(const WCHAR* �ļ�·��, wstring �������Ƽ�, DXGI_FORMAT ������ʽ, float ��������)
{
    int ��� = 1;
    UINT j = 0;
    FbxManager* lFBX���� = NULL;
    FbxScene* l���� = NULL;

    this->������ʽ = ������ʽ;
    this->�������Ƽ� = �������Ƽ�;

    lFBX���� = FbxManager::Create();

    FbxIOSettings* ���� = FbxIOSettings::Create(lFBX����, IOSROOT);
    lFBX����->SetIOSettings(����);
    FbxImporter* l���� = FbxImporter::Create(lFBX����, "");

    char* �ļ����� = 0;
    FbxWCToUTF8(�ļ�·��, �ļ�����, 0);

    if (!l����->Initialize(�ļ�����, -1, ����))
    {
        string bug = "fbx�������";
        bug += l����->GetStatus().GetErrorString();
        bug += " line:";
        bug += to_string(__LINE__) + "\n";
        OutputDebugStringA(bug.c_str());
        PostQuitMessage(0);
    }

    l���� = FbxScene::Create(lFBX����, "myScene");

    l����->Import(l����);
    l����->Destroy();

    m���ڵ� = new S�任�ڵ�;
    m��Ƥ���� = new S��Ƥ����;
    m�������� = new S��������;
    s�������� = new S��������;
    ���� = new C��������;
    FbxNode* ���ڵ� = l����->GetRootNode();
    ��������++;
    m��������.push_back(L"");
    m���ڵ�->�ڵ����� = L"���ڵ�";

    this->����->����.push_back(������Դ->����ͼ);
    this->����->�����ϴ�.resize(1);

    if (���ڵ�)
        for (int i = 0; i < ���ڵ�->GetChildCount(); i++)
            ���ؽڵ�(���ڵ�->GetChild(i));
    ���������();
    �������� = m��������.size();
    ���ز��(l����);
    ��������(l����);

    S������� s�������;
    s�������.Ԥ��ת = XMMatrixIdentity();
    �������.insert(pair<wstring, S�������>(L"���ڵ�", s�������));

    s�����任 = new XMMATRIX[��������];
    for (int i = 0; i < ��������; i++)
        s�����任[i] = XMMatrixIdentity();

    ���㵥Ԫ��С = sizeof(S����);

    ���ض���(l����);
    ���ع���λ����Ϣ();
    �ϲ����嶯����Ϣ();
    �ϲ�������(m���ڵ�);
    �Ż�����();

    s��������->���㼯.resize(m�Ż����㼯.size());
    for (int i = 0; i < m�Ż����㼯.size(); i++)
    {
        s��������->���㼯[i] = m�Ż����㼯[i].����;
    }

    if (s��������->���㼯.size() == 0)
    {
        wstring bug = L"�޶��� line:";
        bug += to_wstring(__LINE__) + L"\n";
        OutputDebugString(bug.c_str());
        PostQuitMessage(0);
    }

    �������� = s��������->���㼯.size();
    ���㲼�� = FVFλ�� | FVF������ | FVF�������� | FVFȨ�� | FVF��������;

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

    ���㼯 = new S����[s��������->���㼯.size()];
    for (int i = 0; i < s��������->���㼯.size(); i++)
        ���㼯[i] = s��������->���㼯[i];

    D3D12_SUBRESOURCE_DATA subResourceData = {};
    subResourceData.pData = ���㼯;
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
        s��������->s����.resize(s��������->����.size());
        for (int i = 0; i < s��������->����.size(); i++)
            s��������->s����[i] = s��������->����[i];
        subResourceData.pData = s��������->s����.data();
        subResourceData.RowPitch = sizeof(USHORT) * s��������->s����.size();
    }
    else if (������ʽ == DXGI_FORMAT_R32_UINT)
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

    ��������������();
    �ͷźϲ�����������();
    �ͷźϲ���Ϣ();

    lFBX����->Destroy();
}

void C��̬����::���ز��(FbxScene* p����)
{
    int i;
    FbxNode* l���ڵ� = p����->GetRootNode();
    m���ڵ�->�ӽڵ����� = l���ڵ�->GetChildCount();
    if(m���ڵ�->�ӽڵ�����)
        m���ڵ�->�ӽڵ� = new S�任�ڵ�[l���ڵ�->GetChildCount()];

    for (i = 0; i < l���ڵ�->GetChildCount(); i++)
    {
        m���ڵ�->�ӽڵ�[i].���ڵ� = m���ڵ�;
        ���ز��(l���ڵ�->GetChild(i), m���ڵ�->�ӽڵ�[i]);
    }
}

void C��̬����::���ز��(FbxNode* p�ڵ�, S�任�ڵ�& �ڵ�)
{
    WCHAR* l�ڵ�����;
    int i = 0;
    int j = 0;

    FbxUTF8ToWC(p�ڵ�->GetName(), l�ڵ�����, 0);
    �ڵ�.�ڵ����� = l�ڵ�����;
    �ڵ�.�ӽڵ����� = p�ڵ�->GetChildCount();
    if(�ڵ�.�ӽڵ�����)
        �ڵ�.�ӽڵ� = new S�任�ڵ�[p�ڵ�->GetChildCount()];

    for (i = 0; i < m�����任.size(); i++)
    {
        if (m��������[i] == l�ڵ�����)
        {
            �ڵ�.�任.λ��.y = m�����任[i].SRT�任.λ��.x;
            �ڵ�.�任.λ��.x = -m�����任[i].SRT�任.λ��.y;
            �ڵ�.�任.λ��.z = m�����任[i].SRT�任.λ��.z;
            �ڵ�.�任.��ת.x = m�����任[i].SRT�任.��ת.x;
            �ڵ�.�任.��ת.y = m�����任[i].SRT�任.��ת.y;
            �ڵ�.�任.��ת.z = m�����任[i].SRT�任.��ת.z;
            �ڵ�.�任.����.x = m�����任[i].SRT�任.����.x;
            �ڵ�.�任.����.y = m�����任[i].SRT�任.����.y;
            �ڵ�.�任.����.z = m�����任[i].SRT�任.����.z;
        }
    }

    for (i = 0; i < p�ڵ�->GetChildCount(); i++)
    {
        �ڵ�.�ӽڵ�[i].���ڵ� = &�ڵ�;
        ���ز��(p�ڵ�->GetChild(i), �ڵ�.�ӽڵ�[i]);
    }
}

void C��̬����::���������()
{
    S�任�ڵ�* p�任�ڵ� = nullptr;
    S�任�ڵ�* p�任�ڵ�2 = nullptr;

    for (int i = 0; i < m��������.size(); i++)
    {
        p�任�ڵ� = nullptr;
        ����������(m��������[i].c_str(), p�任�ڵ�);

        if (p�任�ڵ�)
        {
            p�任�ڵ�2 = nullptr;
            p�任�ڵ�2 = ���ݸ��ڵ�(p�任�ڵ�);
            ����������(p�任�ڵ�2);
        }
    }
}

void C��̬����::����������(S�任�ڵ�* p�����ڵ�)
{
    bool �Ƿ�δ��¼ = false;

    �Ƿ�δ��¼ = true;
    for (int j = 0; j < m��������.size(); j++)
    {
        if (m��������[j].c_str() == p�����ڵ�->�ڵ�����)
        {
            �Ƿ�δ��¼ = false;
        }
    }
    if (�Ƿ�δ��¼)
    {
        m��������.push_back(p�����ڵ�->�ڵ�����);
    }

    for (int i = 0; i < p�����ڵ�->�ӽڵ�����; i++)
    {
        ����������(&p�����ڵ�->�ӽڵ�[i]);
    }
}

C��̬����::S�任�ڵ�* C��̬����::���ݸ��ڵ�(S�任�ڵ�* p�����ڵ�)
{
    S�任�ڵ�* p�����ڵ�2 = p�����ڵ�;
    if(p�����ڵ�2->���ڵ�)
        while (p�����ڵ�2->���ڵ�->�ڵ����� != L"���ڵ�")
        {
            p�����ڵ�2 = p�����ڵ�2->���ڵ�;
        }

    return p�����ڵ�2;
}

void C��̬����::���ؽڵ�(FbxNode* p�ڵ�)
{
    FbxNodeAttribute::EType �ڵ�����{};

    �����������(p�ڵ�);

    if (p�ڵ�->GetNodeAttribute())
    {
        �ڵ����� = p�ڵ�->GetNodeAttribute()->GetAttributeType();

        switch (�ڵ�����)
        {
        case FbxNodeAttribute::eSkeleton:
            ���ع�������(p�ڵ�);
            break;

        case FbxNodeAttribute::eMesh:
            ��������(p�ڵ�);
            ���ع�����Ƥ��Ϣ(p�ڵ�);
            break;

        default:
            break;
        }

        for (int i = 0; i < p�ڵ�->GetChildCount(); ++i)
        {
            ���ؽڵ�(p�ڵ�->GetChild(i));
        }
    }
}

void C��̬����::�����������(FbxNode* p�ڵ�)
{
    S������� s�������;
    FbxVector4 vec4 = p�ڵ�->GetPreRotation(FbxNode::eSourcePivot);
    //FBXSDK_printf("        Pre-Rotation: %f %f %f\n", vec4[0], vec4[1], vec4[2]);
    s�������.Ԥ��ת = XMMatrixRotationRollPitchYaw(vec4[1] * XM_PI / 180, vec4[2] * XM_PI / 180, vec4[0] * XM_PI / 180);
    WCHAR* ����;
    FbxUTF8ToWC(p�ڵ�->GetName(), ����, 0);
    �������.insert(pair<wstring, S�������>(����, s�������));
}

void C��̬����::��������(FbxNode* p����ڵ�)
{
    FbxMesh* p���� = p����ڵ�->GetMesh();
    if (p���� == NULL) return;

    XMFLOAT3 lλ��[3]{};
    XMFLOAT3 l������[3]{};
    XMFLOAT3 l������[3]{};
    XMFLOAT2 l��������[4]{};
    UINT i = 0;
    UINT j = 0;
    UINT k = 0;
    UINT l = 0;
    UINT m = 0;
    UINT l��������� = p����->GetPolygonCount();
    UINT l��ǰ������� = 0;
    UINT l����ζ������� = 0;
    UINT l��ǰ�������� = 0;
    UINT l������������ = 0;

    for (i = 0; i < l���������; i++)
    {
        int ��ǰ����ζ������� = p����->GetPolygonSize(i);
        �������� += (��ǰ����ζ������� - 2) * 3;
        l��ǰ�������� += (��ǰ����ζ������� - 2) * 3;
    }

    s��������->����.resize(��������);
    UINT ���ƶ������� = p����->GetControlPointsCount();

    WCHAR* ��������;
    FbxUTF8ToWC(p����ڵ�->GetName(), ��������);

    m������ƶ��㼯.resize(m������ƶ��㼯.size() + 1);
    m������ƶ��㼯[m������ƶ��㼯.size() - 1].�������� = ��������;
    m������ƶ��㼯[m������ƶ��㼯.size() - 1].���ƶ��㼯.resize(���ƶ�������);

    XMMATRIX ��ת���� = XMMatrixIdentity();
    //��ת���� *= XMMatrixRotationAxis(XMVECTOR{ 0.0f, 1.0f, 0.0f, 0.0f }, XM_PI / 2);
    //��ת���� *= XMMatrixRotationAxis(XMVECTOR{ 0.0f, 0.0f, 1.0f, 0.0f }, XM_PI / 2);

    for (i = 0; i < l���������; i++)
    {
        l����ζ������� = p����->GetPolygonSize(i);
        for (j = 0; j < l����ζ�������; j++)
        {
            int l���ƶ������� = p����->GetPolygonVertex(i, j);
            int id;
            FbxVector4* ���ƶ��� = p����->GetControlPoints();
            S���� ����;
            XMVECTOR ����任 = { 0.0f, 0.0f, 0.0f, 0.0f };
            ����任.m128_f32[0] = ���ƶ���[l���ƶ�������].mData[1];
            ����任.m128_f32[1] = ���ƶ���[l���ƶ�������].mData[2];
            ����任.m128_f32[2] = ���ƶ���[l���ƶ�������].mData[0];
            ����任 = XMVector3TransformCoord(����任, ��ת����);

            ����.λ��.x = ����任.m128_f32[0];
            ����.λ��.y = ����任.m128_f32[1];
            ����.λ��.z = ����任.m128_f32[2];

            FbxGeometryElementUV* p�������� = p����->GetElementUV(0);

            if (p��������)
                switch (p��������->GetMappingMode())
                {
                case FbxGeometryElement::eByControlPoint:
                    switch (p��������->GetReferenceMode())
                    {
                    case FbxGeometryElement::eDirect:
                        ����.��������.x = p��������->GetDirectArray().GetAt(l���ƶ�������).mData[0];
                        ����.��������.y = 1.0f - p��������->GetDirectArray().GetAt(l���ƶ�������).mData[1];
                        break;

                    case FbxGeometryElement::eIndexToDirect:
                        id = p��������->GetIndexArray().GetAt(l���ƶ�������);
                        ����.��������.x = p��������->GetDirectArray().GetAt(id).mData[0];
                        ����.��������.y = 1.0f - p��������->GetDirectArray().GetAt(id).mData[1];
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
                        ����.��������.x = p��������->GetDirectArray().GetAt(p����->GetTextureUVIndex(i, j)).mData[0];
                        ����.��������.y = 1.0f - p��������->GetDirectArray().GetAt(p����->GetTextureUVIndex(i, j)).mData[1];
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
                    ����任.m128_f32[0] = p������->GetDirectArray().GetAt(l���ƶ�������).mData[1];
                    ����任.m128_f32[1] = p������->GetDirectArray().GetAt(l���ƶ�������).mData[2];
                    ����任.m128_f32[2] = p������->GetDirectArray().GetAt(l���ƶ�������).mData[0];
                    ����任 = XMVector3Transform(����任, ��ת����);
                    ����.������.x = ����任.m128_f32[0];
                    ����.������.y = ����任.m128_f32[1];
                    ����.������.z = ����任.m128_f32[2];
                    break;

                case FbxGeometryElement::eIndexToDirect:
                    id = p������->GetIndexArray().GetAt(l���ƶ�������);
                    ����任.m128_f32[0] = p������->GetDirectArray().GetAt(id).mData[1];
                    ����任.m128_f32[1] = p������->GetDirectArray().GetAt(id).mData[2];
                    ����任.m128_f32[2] = p������->GetDirectArray().GetAt(id).mData[0];
                    ����任 = XMVector3Transform(����任, ��ת����);
                    ����.������.x = ����任.m128_f32[0];
                    ����.������.y = ����任.m128_f32[1];
                    ����.������.z = ����任.m128_f32[2];
                    break;

                default:
                    break;
                }
                break;

            case FbxGeometryElement::eByPolygonVertex:
                switch (p������->GetReferenceMode())
                {
                case FbxGeometryElement::eDirect:
                    ����任.m128_f32[0] = p������->GetDirectArray().GetAt(l��ǰ�������).mData[1];
                    ����任.m128_f32[1] = p������->GetDirectArray().GetAt(l��ǰ�������).mData[2];
                    ����任.m128_f32[2] = p������->GetDirectArray().GetAt(l��ǰ�������).mData[0];
                    ����任 = XMVector3Transform(����任, ��ת����);
                    ����.������.x = ����任.m128_f32[0];
                    ����.������.y = ����任.m128_f32[1];
                    ����.������.z = ����任.m128_f32[2];
                    break;

                case FbxGeometryElement::eIndexToDirect:
                    id = p������->GetIndexArray().GetAt(l��ǰ�������);
                    ����任.m128_f32[0] = p������->GetDirectArray().GetAt(id).mData[1];
                    ����任.m128_f32[1] = p������->GetDirectArray().GetAt(id).mData[2];
                    ����任.m128_f32[2] = p������->GetDirectArray().GetAt(id).mData[0];
                    ����任 = XMVector3Transform(����任, ��ת����);
                    ����.������.x = ����任.m128_f32[0];
                    ����.������.y = ����任.m128_f32[1];
                    ����.������.z = ����任.m128_f32[2];
                    break;

                default:
                    break;
                }
                break;
            }

            ��Ӷ���(l���ƶ�������, &����, m�������);
            m�������++;
            l��ǰ�������++;
        }

        for (k = 0; k < l����ζ������� - 2; k++)
        {
            s��������->����[m��������] = m������� - l����ζ�������;
            m��������++;
            s��������->����[m��������] = m������� - k - 1;
            m��������++;
            s��������->����[m��������] = m������� - k - 2;
            m��������++;
        }
    }


    C��������::S����* ���� = new C��������::S����;

    WCHAR* �������� = 0;
    FbxUTF8ToWC(p����ڵ�->GetName(), ��������, 0);
    ����->�������� = ��������;

    ���ز���(p����ڵ�, ����);

    XMMATRIX ��ת����2 = XMMatrixIdentity();
    ��ת����2 *= XMMatrixRotationAxis(XMVECTOR{ 0.0f, 0.0f, 1.0f, 0.0f }, XM_PI / 2);
    XMMATRIX ��ת����3 = XMMatrixRotationAxis(XMVECTOR{ 0.0f, 1.0f, 0.0f, 0.0f }, -XM_PI / 2);

    ����->�������� = l��ǰ��������;
    ����->��ʼ���� = m�������� - l��ǰ��������;
    XMMATRIX ���ž��� = XMMatrixIdentity();
    XMMATRIX ��ת���� = XMMatrixIdentity();
    XMMATRIX λ�ƾ��� = XMMatrixIdentity();
    ���ž��� = XMMatrixScaling(p����ڵ�->LclScaling.Get().mData[0], p����ڵ�->LclScaling.Get().mData[1],
        p����ڵ�->LclScaling.Get().mData[2]);
    float x = p����ڵ�->LclRotation.Get().mData[1];    float y = p����ڵ�->LclRotation.Get().mData[2];    float z = p����ڵ�->LclRotation.Get().mData[0];
    ��ת���� *= XMMatrixRotationRollPitchYaw(p����ڵ�->LclRotation.Get().mData[1] * XM_PI / 180,
        p����ڵ�->LclRotation.Get().mData[2] * XM_PI / 180, p����ڵ�->LclRotation.Get().mData[0] * XM_PI / 180);
    ��ת���� = �������[��������].Ԥ��ת * ��ת����2 * ��ת����;
    λ�ƾ��� *= XMMatrixTranslation(p����ڵ�->LclTranslation.Get().mData[0], p����ڵ�->LclTranslation.Get().mData[1],
        p����ڵ�->LclTranslation.Get().mData[2]);
    λ�ƾ��� = λ�ƾ��� * ��ת����3;
    λ�ƾ���.r[0].m128_f32[0] = 1.0f; λ�ƾ���.r[0].m128_f32[1] = 0.0f; λ�ƾ���.r[0].m128_f32[2] = 0.0f;
    λ�ƾ���.r[1].m128_f32[0] = 0.0f; λ�ƾ���.r[1].m128_f32[1] = 1.0f; λ�ƾ���.r[1].m128_f32[2] = 0.0f;
    λ�ƾ���.r[2].m128_f32[0] = 0.0f; λ�ƾ���.r[2].m128_f32[1] = 0.0f; λ�ƾ���.r[2].m128_f32[2] = 1.0f;
    ����->�任 = ���ž��� * ��ת���� * λ�ƾ���;

    this->����->���Ԫ��(����);
}

void C��̬����::���ز���(FbxNode* p����ڵ�, C��������::S����* ����)
{
    FbxMesh* p���� = p����ڵ�->GetMesh();
    int �������� = 0;

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
        ����->����.����� = 0.0f;
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

    ��������(p�������, ����);
}

void C��̬����::��������(FbxSurfaceMaterial* p�������, C��������::S����* ����)
{
    int i;
    int k = 0;
    int ��� = 1;
    FbxProperty ��������;
    WCHAR* ·�� = 0;

    for (i = 0; i < FbxLayerElement::sTypeTextureCount; i++)
    {
        �������� = p�������->FindProperty(FbxLayerElement::sTextureChannelNames[i]);
        if (��������.IsValid())
        {
            int textureCount = ��������.GetSrcObjectCount();

            for (int j = 0; j < textureCount; ++j)
            {
                FbxFileTexture* p���� = FbxCast<FbxFileTexture>(��������.GetSrcObject(j));
                if (p����)
                {
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

                        this->����->����.resize(this->����->����.size() + 1);
                        this->����->�����ϴ�.resize(this->����->�����ϴ�.size() + 1);
                        if (�ļ����� == L"dds")
                        {
                            if (!SUCCEEDED(CreateDDSTextureFromFile12(�豸.Get(), �������.Get(), ·��, this->����->����[this->����->����.size() - 1],
                                this->����->�����ϴ�[this->����->�����ϴ�.size() - 1])))
                            {
                                wstring bug = L"����ģ�Ͳ���ʱδ�ҵ���ͼ�ļ� line:";
                                bug += to_wstring(__LINE__) + L"\n";
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

void C��̬����::�ϲ�����(UINT ���ƶ��㼯, UINT ���ƶ�������, float ��Сcos�Ƕ�, float ���uv���)
{;
    UINT �������� = 0;
    UINT ��ǰ���� = 0;
    S�Ż����㼯* ���㼯;
    UINT i = 0;
    UINT j = 0;
    UINT k = 0;
    UINT l = 0;
    UINT m = 0;
    UINT n = 0;
    UINT u = 0;
    float Ȩ�غ� = 0;
    UINT ������������ = 0;
    UINT ��С��������;
    float ��СȨ�� = 1.0f;
    bool l���� = 0;

    �������� = m������ƶ��㼯[���ƶ��㼯].���ƶ��㼯[���ƶ�������].size();

    ���㼯 = new S�Ż����㼯[��������];

    //�ϲ�������Ϣ
    for(m = 0; m < ��������; m++)
    {
        ������������ = 0;
        for (i = 0; i < m��Ƥ����->��������.size(); i++)
        {
            if(m��Ƥ����->��������[i].�������� == m������ƶ��㼯[���ƶ��㼯].��������)
            for (k = 0; k < m��Ƥ����->��������[i].����.size(); k++)
            {
                for (l = 0; l < m��Ƥ����->��������[i].����[k].������.size(); l++)
                {
                    if (m��Ƥ����->��������[i].����[k].������[l] == ���ƶ�������)
                    {
                        for (j = 0; j < ��������; j++)
                        {
                            if (m��Ƥ����->��������[i].����[k].�������� == m��������[j])
                            {
                                if (m��Ƥ����->��������[i].����[k].Ȩ����[l] > 0.001)
                                {
                                    //������СȨ�ع���
                                    if (������������ == d��������������)
                                    {
                                        ��СȨ�� = 1.0f;
                                        for (n = 0; n < d�������������� - 1; n++)
                                        {
                                            if (��СȨ�� > m������ƶ��㼯[���ƶ��㼯].���ƶ��㼯[���ƶ�������][m].����.����Ȩ��[n])
                                            {
                                                ��С�������� = n;
                                                ��СȨ�� = m������ƶ��㼯[���ƶ��㼯].���ƶ��㼯[���ƶ�������][m].����.����Ȩ��[n];
                                            }
                                        }

                                        if (��СȨ�� < m��Ƥ����->��������[i].����[k].Ȩ����[l])
                                        {
                                            m������ƶ��㼯[���ƶ��㼯].���ƶ��㼯[���ƶ�������][m].����.����Ȩ��[��С��������] = 
                                                m��Ƥ����->��������[i].����[k].Ȩ����[l] + ��СȨ��;
                                            m������ƶ��㼯[���ƶ��㼯].���ƶ��㼯[���ƶ�������][m].����.������������[��С��������] = j;
                                        }

                                        continue;
                                    }

                                    m������ƶ��㼯[���ƶ��㼯].���ƶ��㼯[���ƶ�������][m].����.������������[������������] = j;
                                    if(������������ < 3)
                                        m������ƶ��㼯[���ƶ��㼯].���ƶ��㼯[���ƶ�������][m].����.����Ȩ��[������������] = 
                                            m��Ƥ����->��������[i].����[k].Ȩ����[l];
                                    ������������++;
                                }
                            }
                        }
                    }
                }
            }
        }

        for (k = ������������; k < d��������������; k++)
        {
            m������ƶ��㼯[���ƶ��㼯].���ƶ��㼯[���ƶ�������][m].����.������������[k] = 0;
            if (k < d�������������� - 1) m������ƶ��㼯[���ƶ��㼯].���ƶ��㼯[���ƶ�������][m].����.����Ȩ��[k] = 0;
        }

        ���㼯[��ǰ����].���� = m������ƶ��㼯[���ƶ��㼯].���ƶ��㼯[���ƶ�������][m].����;
        ���㼯[��ǰ����].���� = m������ƶ��㼯[���ƶ��㼯].���ƶ��㼯[���ƶ�������][m].����;
        ��ǰ����++;
    }

    XMVECTOR ������1, ������2;
    XMVECTOR ����1, ����2;

    for (i = 0; i < ��������; i++)
    {
        for (j = i + 1; j < ��������; j++)
        {
            ������1 = XMLoadFloat3(&���㼯[i].����.������);
            ������2 = XMLoadFloat3(&���㼯[j].����.������);
            ����1 = XMLoadFloat2(&���㼯[i].����.��������);
            ����2 = XMLoadFloat2(&���㼯[j].����.��������);

            if (XMVector3Dot(������1, ������2).m128_f32[0] < ��Сcos�Ƕ� ||
                XMVector2Length(����1 - ����2).m128_f32[0] > ���uv���)
            {
                for (k = 0; k < ��������; k++)
                {
                    m�Ż����㼯.resize(m�Ż����㼯.size() + 1);
                    m�Ż����㼯[m�Ż����㼯.size() - 1].���� = ���㼯[k].����;
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
    m�ϲ�������[m�ϲ�������.size() - 1].��������.resize(��������);

    ������1 = { 0.0f, 0.0f, 0.0f, 0.0f };
    for (i = 0; i < ��������; i++)
    {
        m�ϲ�������[m�ϲ�������.size() - 1].��������[i] = ���㼯[i].����;
        ������1 += XMLoadFloat3(&���㼯[i].����.������);
    }
    ������1 = ������1 / ��������;

    m�Ż����㼯.resize(m�Ż����㼯.size() + 1);
    m�Ż����㼯[m�Ż����㼯.size() - 1].���� = ���㼯[0].����;
    XMStoreFloat3(&m�Ż����㼯[m�Ż����㼯.size() - 1].����.������, ������1);
    m�Ż����㼯[m�Ż����㼯.size() - 1].���� = ���㼯[0].����;

����:
    delete[] ���㼯; ���㼯 = nullptr;
}

void C��̬����::��Ӷ���(UINT ���ƶ�������, S����* ����, UINT ����)
{
    UINT i = 0;

    i = m������ƶ��㼯[m������ƶ��㼯.size() - 1].���ƶ��㼯[���ƶ�������].size();
    m������ƶ��㼯[m������ƶ��㼯.size() - 1].���ƶ��㼯[���ƶ�������].resize(i + 1);

    m������ƶ��㼯[m������ƶ��㼯.size() - 1].���ƶ��㼯[���ƶ�������][i].���� = *����;
    m������ƶ��㼯[m������ƶ��㼯.size() - 1].���ƶ��㼯[���ƶ�������][i].���� = ����;
}

void C��̬����::�Ż�����()
{
    float ��Сcos�Ƕ� = cosf(�������ϲ����Ƕ�);
    UINT i = 0;
    UINT j = 0;
    UINT k = 0;

    for (i = 0; i < m������ƶ��㼯.size(); i++)
        for (j = 0; j < m������ƶ��㼯[i].���ƶ��㼯.size(); j++)
            �ϲ�����(i, j, ��Сcos�Ƕ�, ��ͼ������������);

    thread* �߳� = new thread[�߳�����];
    bool* �Ƿ���� = new bool[�߳�����];

    for (int i = 0; i < �߳�����; i++)
    {
        �Ƿ����[i] = true;
        �߳�[i] = thread(�Ż������̳߳�ʼ��);
    }

    bool �Ƿ���� = true;

    for (i = 0; i < ��������; i++)
    {
        while (1)
        {
            for (int j = 0; j < �߳�����; j++)
            {
                if (�Ƿ����[j] == true)
                {
                    �߳�[j].join();
                    �Ƿ����[j] = false;

                    �߳�[j] = thread(�Ż������߳�, s��������, &m�ϲ�������, i, &�Ƿ����[j]);

                    goto �����߳�;
                }
            }
        }

    �����߳�: continue;
    }

    for (int i = 0; i < �߳�����; i++)
        �߳�[i].join();

    delete[] �߳�;
    delete[] �Ƿ����;
}

void C��̬����::�Ż������߳�(S��������* s��������, vector<S�ϲ�������>* m�ϲ�������, int i, bool* �Ƿ����)
{
    int j = 0;
    int k = 0;

    for (j = 0; j < (*m�ϲ�������).size(); j++)
    {
        for (k = 0; k < (*m�ϲ�������)[j].��������.size(); k++)
        {
            if (s��������->����[i] == (*m�ϲ�������)[j].��������[k])
            {
                s��������->����[i] = (*m�ϲ�������)[j].������;
                *�Ƿ���� = 1;
                return;
            }
        }
    }

    *�Ƿ���� = true;
}

void C��̬����::�Ż������̳߳�ʼ��()
{

}

void C��̬����::���ض���(FbxScene* p����)
{
    m��������->Ƭ��.resize(p����->GetSrcObjectCount<FbxAnimStack>());

    char lTimeString[256]{};

    FbxTime   l֡ʱ��;
    FbxTimeSpan lʱ����;
    FbxTime     l��ʼ, l����;
    FbxGlobalSettings* p�趨 = 0;
    int l֡���� = 0;
    int lʱ = 0;
    int l�� = 0;
    int l�� = 0;
    int l֡ = 0;
    int l�� = 0;
    int l��ֵ = 0;

    l֡���� = l֡ʱ��.GetFrameRate(l֡ʱ��.eDefaultMode);
    m��������->֡���� = l֡����;

    p�趨 = &p����->GetGlobalSettings();

    p�趨->GetTimelineDefaultTimeSpan(lʱ����);
    l��ʼ = lʱ����.GetStart();
    l���� = lʱ����.GetStop();
    l��ʼ.GetTime(lʱ, l��, l��, l֡, l��, l��ֵ);
    m��������->��ʼ֡ = lʱ * l֡���� * l֡���� * l֡���� + l�� * l֡���� * l֡���� + l�� * l֡���� + l֡;
    l����.GetTime(lʱ, l��, l��, l֡, l��, l��ֵ);
    m��������->����֡ = lʱ * l֡���� * l֡���� * l֡���� + l�� * l֡���� * l֡���� + l�� * l֡���� + l֡;

    for (UINT i = 0; i < p����->GetSrcObjectCount<FbxAnimStack>(); i++)
    {
        FbxAnimStack* l����Ƭ�� = p����->GetSrcObject<FbxAnimStack>(i);

        WCHAR* Ƭ������ = 0;
        FbxUTF8ToWC(l����Ƭ��->GetName(),Ƭ������, 0);
        m��������->Ƭ��[i].Ƭ������ = Ƭ������;

        ���ض���Ƭ��(l����Ƭ��, p����->GetRootNode(), i);
    }
}

void C��̬����::���ض���Ƭ��(FbxAnimStack* p����Ƭ��, FbxNode* p�ڵ�, UINT Ƭ������)
{
    int l;
    int ���������� = p����Ƭ��->GetMemberCount<FbxAnimLayer>();
    int ��Ч������ = p����Ƭ��->GetMemberCount<FbxAudioLayer>();
    FbxTimeSpan ʱ����;
    FbxTime l֡ʱ��;
    FbxTime l��ʼ, l����;
    int l֡���� = 0;
    int lʱ = 0;
    int l�� = 0;
    int l�� = 0;
    int l֡ = 0;
    int l�� = 0;
    int l��ֵ = 0;

    if (����������)
        m��������->Ƭ��[Ƭ������].������.resize(����������);

    if (��Ч������)
        m��������->Ƭ��[Ƭ������].��Ч��.resize(��Ч������);

    ʱ���� = p����Ƭ��->GetLocalTimeSpan();
    l֡���� = l֡ʱ��.GetFrameRate(l֡ʱ��.eDefaultMode);

    l��ʼ = ʱ����.GetStart();
    l���� = ʱ����.GetStop();
    l��ʼ.GetTime(lʱ, l��, l��, l֡, l��, l��ֵ);
    m��������->Ƭ��[Ƭ������].��ʼ֡ = lʱ * l֡���� * l֡���� * l֡���� + l�� * l֡���� * l֡���� + l�� * l֡���� + l֡;
    l����.GetTime(lʱ, l��, l��, l֡, l��, l��ֵ);
    m��������->Ƭ��[Ƭ������].����֡ = lʱ * l֡���� * l֡���� * l֡���� + l�� * l֡���� * l֡���� + l�� * l֡���� + l֡;
    m��������->Ƭ��[Ƭ������].֡���� = l֡����;

    for (l = 0; l < ����������; l++)
    {
        FbxAnimLayer* l������ = p����Ƭ��->GetMember<FbxAnimLayer>(l);

        WCHAR* ���������� = 0;
        FbxUTF8ToWC(l������->GetName(), ����������);
        m��������->Ƭ��[Ƭ������].������[l].����������, ���������� = ����������;

        ���ض�����(l������, p�ڵ�, Ƭ������, l);
    }

    for (l = 0; l < ��Ч������; l++)
    {
        FbxAudioLayer* l��Ч�� = p����Ƭ��->GetMember<FbxAudioLayer>(l);
        ������Ч��(l��Ч��, l, Ƭ������);
    }
}

void C��̬����::������Ч��(FbxAudioLayer* p��Ч��, UINT ��Ч������, UINT Ƭ������)
{
    int l��������;
    WCHAR* l��Ч������ = 0;
    WCHAR* l�������� = 0;

    l�������� = p��Ч��->GetMemberCount<FbxAudio>();

    m��������->Ƭ��[Ƭ������].��Ч��[��Ч������].����.resize(l��������);

    FbxUTF8ToWC(p��Ч��->GetName(), l��Ч������);
    m��������->Ƭ��[Ƭ������].��Ч��[��Ч������].��Ч������ = l��Ч������;

    for (int i = 0; i < l��������; i++)
    {
        FbxAudio* l���� = p��Ч��->GetMember<FbxAudio>(i);
        FbxUTF8ToWC(l����->GetName(), l��������, 0);
        m��������->Ƭ��[Ƭ������].��Ч��[��Ч������].����[i].�������� = l��������;
    }
}

void C��̬����::���ض�����(FbxAnimLayer* p������, FbxNode* p�ڵ�, UINT Ƭ������, UINT ����������)
{
    int lģ������;
    WCHAR* l��������;

    for (lģ������ = 0; lģ������ < p�ڵ�->GetChildCount(); lģ������++)
    {
        ���ض�����(p������, p�ڵ�->GetChild(lģ������), Ƭ������, ����������);
    }

    FbxUTF8ToWC(p�ڵ�->GetName(), l��������, 0);
    m��������->Ƭ��[Ƭ������].������[����������].����.resize(m��������->Ƭ��[Ƭ������].������[����������].����.size() + 1);
    m��������->Ƭ��[Ƭ������].������[����������].����[m��������->Ƭ��[Ƭ������].������[����������].����.size() - 1].�������� = l��������;

    ���ض���ͨ��(p������, p�ڵ�, Ƭ������, ����������, m��������->Ƭ��[Ƭ������].������[����������].����.size() - 1);
}

void C��̬����::���ض���ͨ��(FbxAnimLayer* p������, FbxNode* p�ڵ�, UINT Ƭ������, UINT ����������, UINT ģ������)
{
    FbxAnimCurve* l�������� = NULL;

    FbxTime   l֡ʱ��;
    float   lֵ֡;
    int     l֡����;
    int l֡����;

    int lʱ;
    int l��;
    int l��;
    int l֡;
    int l��;
    int l��ֵ;
    int l���� = 0;
    int l���� = 0;

    //��ʾһ�����ߡ�
    l�������� = p�ڵ�->LclTranslation.GetCurve(p������, FBXSDK_CURVENODE_COMPONENT_X);
    if (l��������)
    {
        int l֡���� = l��������->KeyGetCount();
        if (l֡���� > m��������->Ƭ��[Ƭ������].������[����������].����[ģ������].λ��.size())
            m��������->Ƭ��[Ƭ������].������[����������].����[ģ������].λ��.resize(l֡����);

        for (l֡���� = 0; l֡���� < l֡����; l֡����++)
        {
            lֵ֡ = (float)l��������->KeyGetValue(l֡����);
            l֡ʱ�� = l��������->KeyGetTime(l֡����);
            l֡ʱ��.GetTime(lʱ, l��, l��, l֡, l��, l��ֵ);
            l֡���� = l֡ʱ��.GetFrameRate(l֡ʱ��.eDefaultMode);

            m��������->Ƭ��[Ƭ������].������[����������].����[ģ������].λ��[l֡����].֡�� =
                lʱ * l֡���� * l֡���� * l֡���� + l�� * l֡���� * l֡���� + l�� * l֡���� + l֡;
            m��������->Ƭ��[Ƭ������].������[����������].����[ģ������].λ��[l֡����].λ��.x = lֵ֡;
        }
    }
    l�������� = p�ڵ�->LclTranslation.GetCurve(p������, FBXSDK_CURVENODE_COMPONENT_Y);
    if (l��������)
    {
        int l֡���� = l��������->KeyGetCount();
        if (l֡���� > m��������->Ƭ��[Ƭ������].������[����������].����[ģ������].λ��.size())
            m��������->Ƭ��[Ƭ������].������[����������].����[ģ������].λ��.resize(l֡����);

        for (l֡���� = 0; l֡���� < l֡����; l֡����++)
        {
            lֵ֡ = (float)l��������->KeyGetValue(l֡����);
            l֡ʱ�� = l��������->KeyGetTime(l֡����);
            l֡ʱ��.GetTime(lʱ, l��, l��, l֡, l��, l��ֵ);
            l֡���� = l֡ʱ��.GetFrameRate(l֡ʱ��.eDefaultMode);

            m��������->Ƭ��[Ƭ������].������[����������].����[ģ������].λ��[l֡����].֡�� =
                lʱ * l֡���� * l֡���� * l֡���� + l�� * l֡���� * l֡���� + l�� * l֡���� + l֡;
            m��������->Ƭ��[Ƭ������].������[����������].����[ģ������].λ��[l֡����].λ��.y = lֵ֡;
        }
    }
    l�������� = p�ڵ�->LclTranslation.GetCurve(p������, FBXSDK_CURVENODE_COMPONENT_Z);
    if (l��������)
    {
        int l֡���� = l��������->KeyGetCount();
        if (l֡���� > m��������->Ƭ��[Ƭ������].������[����������].����[ģ������].λ��.size())
            m��������->Ƭ��[Ƭ������].������[����������].����[ģ������].λ��.resize(l֡����);

        for (l֡���� = 0; l֡���� < l֡����; l֡����++)
        {
            lֵ֡ = (float)l��������->KeyGetValue(l֡����);
            l֡ʱ�� = l��������->KeyGetTime(l֡����);
            l֡ʱ��.GetTime(lʱ, l��, l��, l֡, l��, l��ֵ);
            l֡���� = l֡ʱ��.GetFrameRate(l֡ʱ��.eDefaultMode);

            m��������->Ƭ��[Ƭ������].������[����������].����[ģ������].λ��[l֡����].֡�� =
                lʱ * l֡���� * l֡���� * l֡���� + l�� * l֡���� * l֡���� + l�� * l֡���� + l֡;
            m��������->Ƭ��[Ƭ������].������[����������].����[ģ������].λ��[l֡����].λ��.z = lֵ֡;
        }
    }

    l�������� = p�ڵ�->LclRotation.GetCurve(p������, FBXSDK_CURVENODE_COMPONENT_X);
    if (l��������)
    {
        int l֡���� = l��������->KeyGetCount();
        if (l֡���� > m��������->Ƭ��[Ƭ������].������[����������].����[ģ������].��ת.size())
            m��������->Ƭ��[Ƭ������].������[����������].����[ģ������].��ת.resize(l֡����);

        for (l֡���� = 0; l֡���� < l֡����; l֡����++)
        {
            lֵ֡ = (float)l��������->KeyGetValue(l֡����);
            l֡ʱ�� = l��������->KeyGetTime(l֡����);
            l֡ʱ��.GetTime(lʱ, l��, l��, l֡, l��, l��ֵ);
            l֡���� = l֡ʱ��.GetFrameRate(l֡ʱ��.eDefaultMode);

            m��������->Ƭ��[Ƭ������].������[����������].����[ģ������].��ת[l֡����].֡�� =
                lʱ * l֡���� * l֡���� * l֡���� + l�� * l֡���� * l֡���� + l�� * l֡���� + l֡;
            m��������->Ƭ��[Ƭ������].������[����������].����[ģ������].��ת[l֡����].��ת.x = lֵ֡;
        }
    }
    l�������� = p�ڵ�->LclRotation.GetCurve(p������, FBXSDK_CURVENODE_COMPONENT_Y);
    if (l��������)
    {
        int l֡���� = l��������->KeyGetCount();
        if(l֡���� > m��������->Ƭ��[Ƭ������].������[����������].����[ģ������].��ת.size())
            m��������->Ƭ��[Ƭ������].������[����������].����[ģ������].��ת.resize(l֡����);

        for (l֡���� = 0; l֡���� < l֡����; l֡����++)
        {
            lֵ֡ = (float)l��������->KeyGetValue(l֡����);
            l֡ʱ�� = l��������->KeyGetTime(l֡����);
            l֡ʱ��.GetTime(lʱ, l��, l��, l֡, l��, l��ֵ);
            l֡���� = l֡ʱ��.GetFrameRate(l֡ʱ��.eDefaultMode);

            m��������->Ƭ��[Ƭ������].������[����������].����[ģ������].��ת[l֡����].֡�� =
                lʱ * l֡���� * l֡���� * l֡���� + l�� * l֡���� * l֡���� + l�� * l֡���� + l֡;
            m��������->Ƭ��[Ƭ������].������[����������].����[ģ������].��ת[l֡����].��ת.y = lֵ֡;
        }
    }
    l�������� = p�ڵ�->LclRotation.GetCurve(p������, FBXSDK_CURVENODE_COMPONENT_Z);
    if (l��������)
    {
        int l֡���� = l��������->KeyGetCount();
        if (l֡���� > m��������->Ƭ��[Ƭ������].������[����������].����[ģ������].��ת.size())
            m��������->Ƭ��[Ƭ������].������[����������].����[ģ������].��ת.resize(l֡����);

        for (l֡���� = 0; l֡���� < l֡����; l֡����++)
        {
            lֵ֡ = (float)l��������->KeyGetValue(l֡����);
            l֡ʱ�� = l��������->KeyGetTime(l֡����);
            l֡ʱ��.GetTime(lʱ, l��, l��, l֡, l��, l��ֵ);
            l֡���� = l֡ʱ��.GetFrameRate(l֡ʱ��.eDefaultMode);

            m��������->Ƭ��[Ƭ������].������[����������].����[ģ������].��ת[l֡����].֡�� =
                lʱ * l֡���� * l֡���� * l֡���� + l�� * l֡���� * l֡���� + l�� * l֡���� + l֡;
            m��������->Ƭ��[Ƭ������].������[����������].����[ģ������].��ת[l֡����].��ת.z = lֵ֡;
        }
    }

    l�������� = p�ڵ�->LclScaling.GetCurve(p������, FBXSDK_CURVENODE_COMPONENT_X);
    if (l��������)
    {
        int l֡���� = l��������->KeyGetCount();
        if (l֡���� > m��������->Ƭ��[Ƭ������].������[����������].����[ģ������].����.size())
            m��������->Ƭ��[Ƭ������].������[����������].����[ģ������].����.resize(l֡����);

        for (l֡���� = 0; l֡���� < l֡����; l֡����++)
        {
            lֵ֡ = (float)l��������->KeyGetValue(l֡����);
            l֡ʱ�� = l��������->KeyGetTime(l֡����);
            l֡ʱ��.GetTime(lʱ, l��, l��, l֡, l��, l��ֵ);
            l֡���� = l֡ʱ��.GetFrameRate(l֡ʱ��.eDefaultMode);

            m��������->Ƭ��[Ƭ������].������[����������].����[ģ������].����[l֡����].֡�� =
                lʱ * l֡���� * l֡���� * l֡���� + l�� * l֡���� * l֡���� + l�� * l֡���� + l֡;
            m��������->Ƭ��[Ƭ������].������[����������].����[ģ������].����[l֡����].����.x = lֵ֡;
        }
    }
    l�������� = p�ڵ�->LclScaling.GetCurve(p������, FBXSDK_CURVENODE_COMPONENT_Y);
    if (l��������)
    {
        int l֡���� = l��������->KeyGetCount();
        if (l֡���� > m��������->Ƭ��[Ƭ������].������[����������].����[ģ������].����.size())
            m��������->Ƭ��[Ƭ������].������[����������].����[ģ������].����.resize(l֡����);

        for (l֡���� = 0; l֡���� < l֡����; l֡����++)
        {
            lֵ֡ = (float)l��������->KeyGetValue(l֡����);
            l֡ʱ�� = l��������->KeyGetTime(l֡����);
            l֡ʱ��.GetTime(lʱ, l��, l��, l֡, l��, l��ֵ);
            l֡���� = l֡ʱ��.GetFrameRate(l֡ʱ��.eDefaultMode);

            m��������->Ƭ��[Ƭ������].������[����������].����[ģ������].����[l֡����].֡�� =
                lʱ * l֡���� * l֡���� * l֡���� + l�� * l֡���� * l֡���� + l�� * l֡���� + l֡;
            m��������->Ƭ��[Ƭ������].������[����������].����[ģ������].����[l֡����].����.y = lֵ֡;
        }
    }
    l�������� = p�ڵ�->LclScaling.GetCurve(p������, FBXSDK_CURVENODE_COMPONENT_Z);
    if (l��������)
    {
        int l֡���� = l��������->KeyGetCount();
        if (l֡���� > m��������->Ƭ��[Ƭ������].������[����������].����[ģ������].����.size())
            m��������->Ƭ��[Ƭ������].������[����������].����[ģ������].����.resize(l֡����);

        for (l֡���� = 0; l֡���� < l֡����; l֡����++)
        {
            lֵ֡ = (float)l��������->KeyGetValue(l֡����);
            l֡ʱ�� = l��������->KeyGetTime(l֡����);
            l֡ʱ��.GetTime(lʱ, l��, l��, l֡, l��, l��ֵ);
            l֡���� = l֡ʱ��.GetFrameRate(l֡ʱ��.eDefaultMode);

            m��������->Ƭ��[Ƭ������].������[����������].����[ģ������].����[l֡����].֡�� =
                lʱ * l֡���� * l֡���� * l֡���� + l�� * l֡���� * l֡���� + l�� * l֡���� + l֡;
            m��������->Ƭ��[Ƭ������].������[����������].����[ģ������].����[l֡����].����.z = lֵ֡;
        }
    }

    //��ʾ�ض��ڵƹ���ǵ����ߡ�
    FbxNodeAttribute* l�ڵ����� = p�ڵ�->GetNodeAttribute();

    if (l�ڵ�����)
    {
        l�������� = l�ڵ�����->Color.GetCurve(p������, FBXSDK_CURVENODE_COLOR_RED);
        if (l��������)
        {
            int l֡���� = l��������->KeyGetCount();
            if (l֡���� > m��������->Ƭ��[Ƭ������].������[����������].����[ģ������].��ɫ.size())
                m��������->Ƭ��[Ƭ������].������[����������].����[ģ������].��ɫ.resize(l֡����);

            for (l֡���� = 0; l֡���� < l֡����; l֡����++)
            {
                lֵ֡ = (float)l��������->KeyGetValue(l֡����);
                l֡ʱ�� = l��������->KeyGetTime(l֡����);
                l֡ʱ��.GetTime(lʱ, l��, l��, l֡, l��, l��ֵ);
                l֡���� = l֡ʱ��.GetFrameRate(l֡ʱ��.eDefaultMode);

                m��������->Ƭ��[Ƭ������].������[����������].����[ģ������].��ɫ[l֡����].֡�� =
                    lʱ * l֡���� * l֡���� * l֡���� + l�� * l֡���� * l֡���� + l�� * l֡���� + l֡;
                m��������->Ƭ��[Ƭ������].������[����������].����[ģ������].��ɫ[l֡����].��ɫ.x = lֵ֡;
            }
        }
        l�������� = l�ڵ�����->Color.GetCurve(p������, FBXSDK_CURVENODE_COLOR_GREEN);
        if (l��������)
        {
            int l֡���� = l��������->KeyGetCount();
            if (l֡���� > m��������->Ƭ��[Ƭ������].������[����������].����[ģ������].��ɫ.size())
                m��������->Ƭ��[Ƭ������].������[����������].����[ģ������].��ɫ.resize(l֡����);

            for (l֡���� = 0; l֡���� < l֡����; l֡����++)
            {
                lֵ֡ = (float)l��������->KeyGetValue(l֡����);
                l֡ʱ�� = l��������->KeyGetTime(l֡����);
                l֡ʱ��.GetTime(lʱ, l��, l��, l֡, l��, l��ֵ);
                l֡���� = l֡ʱ��.GetFrameRate(l֡ʱ��.eDefaultMode);

                m��������->Ƭ��[Ƭ������].������[����������].����[ģ������].��ɫ[l֡����].֡�� =
                    lʱ * l֡���� * l֡���� * l֡���� + l�� * l֡���� * l֡���� + l�� * l֡���� + l֡;
                m��������->Ƭ��[Ƭ������].������[����������].����[ģ������].��ɫ[l֡����].��ɫ.y = lֵ֡;
            }
        }
        l�������� = l�ڵ�����->Color.GetCurve(p������, FBXSDK_CURVENODE_COLOR_BLUE);
        if (l��������)
        {
            int l֡���� = l��������->KeyGetCount();
            if (l֡���� > m��������->Ƭ��[Ƭ������].������[����������].����[ģ������].��ɫ.size())
                m��������->Ƭ��[Ƭ������].������[����������].����[ģ������].��ɫ.resize(l֡����);

            for (l֡���� = 0; l֡���� < l֡����; l֡����++)
            {
                lֵ֡ = (float)l��������->KeyGetValue(l֡����);
                l֡ʱ�� = l��������->KeyGetTime(l֡����);
                l֡ʱ��.GetTime(lʱ, l��, l��, l֡, l��, l��ֵ);
                l֡���� = l֡ʱ��.GetFrameRate(l֡ʱ��.eDefaultMode);

                m��������->Ƭ��[Ƭ������].������[����������].����[ģ������].��ɫ[l֡����].֡�� =
                    lʱ * l֡���� * l֡���� * l֡���� + l�� * l֡���� * l֡���� + l�� * l֡���� + l֡;
                m��������->Ƭ��[Ƭ������].������[����������].����[ģ������].��ɫ[l֡����].��ɫ.z = lֵ֡;
            }
        }

        //��ʾ�ض��ڵƹ�����ߡ�
        FbxLight* l��Դ = p�ڵ�->GetLight();
        if (l��Դ)
        {
            l�������� = l��Դ->Intensity.GetCurve(p������);
            if (l��������)
            {
                int l֡���� = l��������->KeyGetCount();
                if (l֡���� > m��������->Ƭ��[Ƭ������].������[����������].����[ģ������].�ƹ�����.size())
                    m��������->Ƭ��[Ƭ������].������[����������].����[ģ������].�ƹ�����.resize(l֡����);

                for (l֡���� = 0; l֡���� < l֡����; l֡����++)
                {
                    lֵ֡ = (float)l��������->KeyGetValue(l֡����);
                    l֡ʱ�� = l��������->KeyGetTime(l֡����);
                    l֡ʱ��.GetTime(lʱ, l��, l��, l֡, l��, l��ֵ);
                    l֡���� = l֡ʱ��.GetFrameRate(l֡ʱ��.eDefaultMode);

                    m��������->Ƭ��[Ƭ������].������[����������].����[ģ������].�ƹ�����[l֡����].֡�� =
                        lʱ * l֡���� * l֡���� * l֡���� + l�� * l֡���� * l֡���� + l�� * l֡���� + l֡;
                    m��������->Ƭ��[Ƭ������].������[����������].����[ģ������].�ƹ�����[l֡����].ǿ�� = lֵ֡;
                }
            }

            l�������� = l��Դ->OuterAngle.GetCurve(p������);
            if (l��������)
            {
                int l֡���� = l��������->KeyGetCount();
                if (l֡���� > m��������->Ƭ��[Ƭ������].������[����������].����[ģ������].�ƹ�����.size())
                    m��������->Ƭ��[Ƭ������].������[����������].����[ģ������].�ƹ�����.resize(l֡����);

                for (l֡���� = 0; l֡���� < l֡����; l֡����++)
                {
                    lֵ֡ = (float)l��������->KeyGetValue(l֡����);
                    l֡ʱ�� = l��������->KeyGetTime(l֡����);
                    l֡ʱ��.GetTime(lʱ, l��, l��, l֡, l��, l��ֵ);
                    l֡���� = l֡ʱ��.GetFrameRate(l֡ʱ��.eDefaultMode);

                    m��������->Ƭ��[Ƭ������].������[����������].����[ģ������].�ƹ�����[l֡����].֡�� =
                        lʱ * l֡���� * l֡���� * l֡���� + l�� * l֡���� * l֡���� + l�� * l֡���� + l֡;
                    m��������->Ƭ��[Ƭ������].������[����������].����[ģ������].�ƹ�����[l֡����].��� = lֵ֡;
                }
            }

            l�������� = l��Դ->Fog.GetCurve(p������);
            if (l��������)
            {
                int l֡���� = l��������->KeyGetCount();
                if (l֡���� > m��������->Ƭ��[Ƭ������].������[����������].����[ģ������].�ƹ�����.size())
                    m��������->Ƭ��[Ƭ������].������[����������].����[ģ������].�ƹ�����.resize(l֡����);

                for (l֡���� = 0; l֡���� < l֡����; l֡����++)
                {
                    lֵ֡ = (float)l��������->KeyGetValue(l֡����);
                    l֡ʱ�� = l��������->KeyGetTime(l֡����);
                    l֡ʱ��.GetTime(lʱ, l��, l��, l֡, l��, l��ֵ);
                    l֡���� = l֡ʱ��.GetFrameRate(l֡ʱ��.eDefaultMode);

                    m��������->Ƭ��[Ƭ������].������[����������].����[ģ������].�ƹ�����[l֡����].֡�� =
                        lʱ * l֡���� * l֡���� * l֡���� + l�� * l֡���� * l֡���� + l�� * l֡���� + l֡;
                    m��������->Ƭ��[Ƭ������].������[����������].����[ģ������].�ƹ�����[l֡����].�� = lֵ֡;
                }
            }
        }

        //��ʾ�ض�������������ߡ�
        FbxCamera* l��� = p�ڵ�->GetCamera();
        if (l���)
        {
            l�������� = l���->FieldOfView.GetCurve(p������);
            if (l��������)
            {

            }

            l�������� = l���->FieldOfViewX.GetCurve(p������);
            if (l��������)
            {
            }

            l�������� = l���->FieldOfViewY.GetCurve(p������);
            if (l��������)
            {

            }

            l�������� = l���->OpticalCenterX.GetCurve(p������);
            if (l��������)
            {

            }

            l�������� = l���->OpticalCenterY.GetCurve(p������);
            if (l��������)
            {

            }

            l�������� = l���->Roll.GetCurve(p������);
            if (l��������)
            {

            }
        }

        //��ʾ�ض��ڼ��ε����ߡ�
        if (l�ڵ�����->GetAttributeType() == FbxNodeAttribute::eMesh ||
            l�ڵ�����->GetAttributeType() == FbxNodeAttribute::eNurbs ||
            l�ڵ�����->GetAttributeType() == FbxNodeAttribute::ePatch)
        {

        }
    }

    //��ʾ�ض������Ե�����
    FbxProperty l���� = p�ڵ�->GetFirstProperty();
}

void C��̬����::���ع�������(FbxNode* p�����ڵ�)
{
    WCHAR* l�������� = 0;
    size_t l����;
    SSRT�任 l�任;

    FbxUTF8ToWC(p�����ڵ�->GetName(), l��������, &l����);

    l�任.����.x = p�����ڵ�->LclScaling.Get().mData[1];
    l�任.����.y = p�����ڵ�->LclScaling.Get().mData[2];
    l�任.����.z = p�����ڵ�->LclScaling.Get().mData[0];
    l�任.��ת.x = p�����ڵ�->LclRotation.Get().mData[1];
    l�任.��ת.y = p�����ڵ�->LclRotation.Get().mData[2];
    l�任.��ת.z = p�����ڵ�->LclRotation.Get().mData[0];
    l�任.λ��.x = p�����ڵ�->LclTranslation.Get().mData[1];
    l�任.λ��.y = p�����ڵ�->LclTranslation.Get().mData[2];
    l�任.λ��.z = p�����ڵ�->LclTranslation.Get().mData[0];

    ��������++;
    m��������.resize(��������);
    m��������[�������� - 1] = l��������;
    m�����任.resize(��������);
    m�����任[�������� - 1].SRT�任 = l�任;
}

void C��̬����::���ع�����Ƥ��Ϣ(FbxNode* p����ڵ�)
{
    int i, j, k;
    int l������ = 0;
    int l�������� = 0;
    FbxCluster* l��;
    WCHAR* l�������� = 0;
    WCHAR* l�������� = 0;
    XMMATRIX ��ת���� = XMMatrixIdentity();
    XMMATRIX ��ת = XMMatrixIdentity();

    FbxGeometry* p���� = (FbxMesh*)p����ڵ�->GetNodeAttribute();
    l������ = p����->GetDeformerCount(FbxDeformer::eSkin);
    FbxUTF8ToWC(p����ڵ�->GetName(), l��������, 0);
    m��Ƥ����->��������.resize(m��Ƥ����->��������.size() + 1);
    m��Ƥ����->��������[m��Ƥ����->��������.size() - 1].�������� = l��������;

    for (i = 0; i != l������; i++)
    {
        l�������� = ((FbxSkin*)p����->GetDeformer(i, FbxDeformer::eSkin))->GetClusterCount();
        m��Ƥ����->��������[m��Ƥ����->��������.size() - 1].����.resize(l��������);
        for (j = 0; j != l��������; j++)
        {
            l�� = ((FbxSkin*)p����->GetDeformer(i, FbxDeformer::eSkin))->GetCluster(j);

            FbxUTF8ToWC(l��->GetLink()->GetName(), l��������, 0);
            m��Ƥ����->��������[m��Ƥ����->��������.size() - 1].����[j].�������� = l��������;

            int l�������� = l��->GetControlPointIndicesCount();
            int* l���� = l��->GetControlPointIndices();
            double* lȨ�� = l��->GetControlPointWeights();

            m��Ƥ����->��������[m��Ƥ����->��������.size() - 1].����[j].������.resize(l��������);
            m��Ƥ����->��������[m��Ƥ����->��������.size() - 1].����[j].Ȩ����.resize(l��������);

            for (k = 0; k < l��������; k++)
            {
                m��Ƥ����->��������[m��Ƥ����->��������.size() - 1].����[j].������[k] = l����[k];
                m��Ƥ����->��������[m��Ƥ����->��������.size() - 1].����[j].Ȩ����[k] = (float)lȨ��[k];
            }

            FbxAMatrix l����;

            l���� = l��->GetTransformMatrix(l����);
            m��Ƥ����->��������[m��Ƥ����->��������.size() - 1].����[j].����ģ��λ��.x = l����.GetT().mData[0];
            m��Ƥ����->��������[m��Ƥ����->��������.size() - 1].����[j].����ģ��λ��.y = l����.GetT().mData[1];
            m��Ƥ����->��������[m��Ƥ����->��������.size() - 1].����[j].����ģ��λ��.z = l����.GetT().mData[2];
            m��Ƥ����->��������[m��Ƥ����->��������.size() - 1].����[j].����ģ����ת.x = l����.GetR().mData[0];
            m��Ƥ����->��������[m��Ƥ����->��������.size() - 1].����[j].����ģ����ת.y = l����.GetR().mData[1];
            m��Ƥ����->��������[m��Ƥ����->��������.size() - 1].����[j].����ģ����ת.z = l����.GetR().mData[2];
            m��Ƥ����->��������[m��Ƥ����->��������.size() - 1].����[j].����ģ������.x = l����.GetS().mData[0];
            m��Ƥ����->��������[m��Ƥ����->��������.size() - 1].����[j].����ģ������.y = l����.GetS().mData[1];
            m��Ƥ����->��������[m��Ƥ����->��������.size() - 1].����[j].����ģ������.z = l����.GetS().mData[2];

            l���� = l��->GetTransformLinkMatrix(l����);
            ��ת����.r[0].m128_f32[0] = l����.mData[1][0]; ��ת����.r[0].m128_f32[1] = l����.mData[1][1]; 
            ��ת����.r[0].m128_f32[2] = l����.mData[1][2];
            ��ת����.r[1].m128_f32[0] = l����.mData[2][0]; ��ת����.r[1].m128_f32[1] = l����.mData[2][1];
            ��ת����.r[1].m128_f32[2] = l����.mData[2][2];
            ��ת����.r[2].m128_f32[0] = l����.mData[0][0]; ��ת����.r[2].m128_f32[1] = l����.mData[0][1];
            ��ת����.r[2].m128_f32[2] = l����.mData[0][2];
            ��ת����.r[3].m128_f32[0] = l����.mData[3][0]; ��ת����.r[3].m128_f32[1] = l����.mData[3][1];
            ��ת����.r[3].m128_f32[2] = l����.mData[3][2];
            ��ת = XMMatrixRotationY(-90 * XM_PI / 180);
            ��ת���� = ��ת���� * ��ת;
            ��ת����.r[3].m128_f32[0] = l����.mData[3][2]; ��ת����.r[3].m128_f32[1] = l����.mData[3][1];
            ��ת����.r[3].m128_f32[2] = -l����.mData[3][0];

            m��Ƥ����->��������[m��Ƥ����->��������.size() - 1].����[j].����������ת���� = ��ת����;
            m��Ƥ����->��������[m��Ƥ����->��������.size() - 1].����[j].��������λ��.x = -l����.GetT().mData[2];
            m��Ƥ����->��������[m��Ƥ����->��������.size() - 1].����[j].��������λ��.y = l����.GetT().mData[1];
            m��Ƥ����->��������[m��Ƥ����->��������.size() - 1].����[j].��������λ��.z = l����.GetT().mData[0];
            m��Ƥ����->��������[m��Ƥ����->��������.size() - 1].����[j].����������ת.x = l����.GetR().mData[2];
            m��Ƥ����->��������[m��Ƥ����->��������.size() - 1].����[j].����������ת.y = l����.GetR().mData[1];
            m��Ƥ����->��������[m��Ƥ����->��������.size() - 1].����[j].����������ת.z = l����.GetR().mData[0];
            m��Ƥ����->��������[m��Ƥ����->��������.size() - 1].����[j].������������.x = l����.GetS().mData[2];
            m��Ƥ����->��������[m��Ƥ����->��������.size() - 1].����[j].������������.y = l����.GetS().mData[1];
            m��Ƥ����->��������[m��Ƥ����->��������.size() - 1].����[j].������������.z = l����.GetS().mData[0];
        }
    }

    l������ = p����->GetDeformerCount(FbxDeformer::eBlendShape);

    for (int i = 0; i < l������; i++)
    {
        l�������� = ((FbxSkin*)p����->GetDeformer(i, FbxDeformer::eSkin))->GetClusterCount();
    }
}

void C��̬����::��������(FbxScene* p����)
{
    int      i, j, k, l��������;
    FbxString  l����;
    FbxNode* l�ڵ� = nullptr;
    WCHAR* �������� = nullptr;
    ���� = new S����;

    l�������� = p����->GetPoseCount();

    for (i = 0; i < l��������; i++)
    {
        FbxPose* l���� = p����->GetPose(i);

        l���� = l����->GetName();
        FbxUTF8ToWC(l����->GetName(), ��������, 0);

        for (j = 0; j < l����->GetCount(); j++)
        {

            l���� = l����->GetNodeName(j).GetCurrentName();
            FbxUTF8ToWC(l����->GetNodeName(j).GetCurrentName(), ��������, 0);

            FbxString lMatrixValue;
            XMMATRIX �󶨾��� = XMMatrixIdentity();

            for (k = 0; k < 4; k++)
            {
                FbxMatrix  l���� = l����->GetMatrix(j);
                FbxVector4 l�� = l����.GetRow(k);

                �󶨾���.r[k].m128_f32[0] = l��[0]; �󶨾���.r[k].m128_f32[1] = l��[1];
                �󶨾���.r[k].m128_f32[2] = l��[2]; �󶨾���.r[k].m128_f32[3] = l��[3];
            }

            XMVECTOR ����λ��{};
            ����λ��.m128_f32[0] = -�󶨾���.r[3].m128_f32[2]; ����λ��.m128_f32[1] = �󶨾���.r[3].m128_f32[1];
            ����λ��.m128_f32[2] = �󶨾���.r[3].m128_f32[0];

            �󶨾���.r[1].m128_f32[0] = -�󶨾���.r[1].m128_f32[0]; �󶨾���.r[1].m128_f32[1] = -�󶨾���.r[1].m128_f32[1];
            �󶨾���.r[1].m128_f32[2] = -�󶨾���.r[1].m128_f32[2];
            �󶨾���.r[0].m128_f32[2] = -�󶨾���.r[0].m128_f32[2]; �󶨾���.r[1].m128_f32[2] = -�󶨾���.r[1].m128_f32[2];
            �󶨾���.r[2].m128_f32[2] = -�󶨾���.r[2].m128_f32[2];

            XMMATRIX �󶨾���2 = �󶨾���;

            �󶨾���2.r[0].m128_f32[0] = �󶨾���.r[0].m128_f32[2]; �󶨾���2.r[1].m128_f32[0] = �󶨾���.r[1].m128_f32[2];
            �󶨾���2.r[2].m128_f32[0] = �󶨾���.r[2].m128_f32[2]; 
            �󶨾���2.r[0].m128_f32[2] = �󶨾���.r[0].m128_f32[0]; �󶨾���2.r[1].m128_f32[2] = �󶨾���.r[1].m128_f32[0];
            �󶨾���2.r[2].m128_f32[2] = �󶨾���.r[2].m128_f32[0]; 

            �󶨾��� = �󶨾���2;

            �󶨾���2.r[0].m128_f32[0] = -�󶨾���.r[1].m128_f32[0]; �󶨾���2.r[0].m128_f32[1] = -�󶨾���.r[1].m128_f32[1];
            �󶨾���2.r[0].m128_f32[2] = -�󶨾���.r[1].m128_f32[2];
            �󶨾���2.r[1].m128_f32[0] = �󶨾���.r[2].m128_f32[0]; �󶨾���2.r[1].m128_f32[1] = �󶨾���.r[2].m128_f32[1];
            �󶨾���2.r[1].m128_f32[2] = �󶨾���.r[2].m128_f32[2];
            �󶨾���2.r[2].m128_f32[0] = �󶨾���.r[0].m128_f32[0]; �󶨾���2.r[2].m128_f32[1] = �󶨾���.r[0].m128_f32[1];
            �󶨾���2.r[2].m128_f32[2] = �󶨾���.r[0].m128_f32[2];

            �󶨾���2.r[3].m128_f32[0] = ����λ��.m128_f32[0]; �󶨾���2.r[3].m128_f32[1] = ����λ��.m128_f32[1];
            �󶨾���2.r[3].m128_f32[2] = ����λ��.m128_f32[2];

            ����->������.insert(pair<wstring, XMMATRIX>(��������, �󶨾���2));
        }
    }

    XMMATRIX �󶨾��� = XMMatrixIdentity();
    ����->������.insert(pair<wstring, XMMATRIX>(L"���ڵ�", �󶨾���));

    l�������� = p����->GetCharacterPoseCount();

    for (i = 0; i < l��������; i++)
    {
        FbxCharacterPose* l���� = p����->GetCharacterPose(i);
        FbxCharacter* l��ɫ = l����->GetCharacter();

        if (!l��ɫ) break;

        FbxUTF8ToWC(l��ɫ->GetName(), ��������, 0);

        FbxCharacterLink l��ɫ����;
        FbxCharacter::ENodeId  l�ڵ�id = FbxCharacter::eHips;

        while (l��ɫ->GetCharacterLink(l�ڵ�id, &l��ɫ����))
        {
            FbxAMatrix& lGlobalPosition = l��ɫ����.mNode->EvaluateGlobalTransform(FBXSDK_TIME_ZERO);

            FbxString lMatrixValue;
            XMMATRIX ��ɫ���� = XMMatrixIdentity();

            for (k = 0; k < 4; k++)
            {
                FbxVector4 lRow = lGlobalPosition.GetRow(k);

                ��ɫ����.r[k].m128_f32[0] = lRow[0]; ��ɫ����.r[k].m128_f32[1] = lRow[1];
                ��ɫ����.r[k].m128_f32[2] = lRow[2]; ��ɫ����.r[k].m128_f32[3] = lRow[3];
            }

            XMMATRIX ��ɫ����2 = XMMatrixIdentity();

            XMVECTOR ����λ��{};
            ����λ��.m128_f32[0] = -��ɫ����.r[3].m128_f32[2]; ����λ��.m128_f32[1] = ��ɫ����.r[3].m128_f32[1];
            ����λ��.m128_f32[2] = ��ɫ����.r[3].m128_f32[0];

            ��ɫ����.r[1].m128_f32[0] = -��ɫ����.r[1].m128_f32[0]; ��ɫ����.r[1].m128_f32[1] = -��ɫ����.r[1].m128_f32[1];
            ��ɫ����.r[1].m128_f32[2] = -��ɫ����.r[1].m128_f32[2];
            ��ɫ����.r[0].m128_f32[2] = -��ɫ����.r[0].m128_f32[2]; ��ɫ����.r[1].m128_f32[2] = -��ɫ����.r[1].m128_f32[2];
            ��ɫ����.r[2].m128_f32[2] = -��ɫ����.r[2].m128_f32[2];

            ��ɫ����2 = ��ɫ����;

            ��ɫ����2.r[0].m128_f32[0] = ��ɫ����.r[0].m128_f32[2]; ��ɫ����2.r[1].m128_f32[0] = ��ɫ����.r[1].m128_f32[2];
            ��ɫ����2.r[2].m128_f32[0] = ��ɫ����.r[2].m128_f32[2];
            ��ɫ����2.r[0].m128_f32[2] = ��ɫ����.r[0].m128_f32[0]; ��ɫ����2.r[1].m128_f32[2] = ��ɫ����.r[1].m128_f32[0];
            ��ɫ����2.r[2].m128_f32[2] = ��ɫ����.r[2].m128_f32[0];

            ��ɫ���� = ��ɫ����2;

            ��ɫ����2.r[0].m128_f32[0] = -��ɫ����.r[1].m128_f32[0]; ��ɫ����2.r[0].m128_f32[1] = ��ɫ����.r[1].m128_f32[1];
            ��ɫ����2.r[0].m128_f32[2] = ��ɫ����.r[1].m128_f32[2];
            ��ɫ����2.r[1].m128_f32[0] = ��ɫ����.r[2].m128_f32[0]; ��ɫ����2.r[1].m128_f32[1] = ��ɫ����.r[2].m128_f32[1];
            ��ɫ����2.r[1].m128_f32[2] = ��ɫ����.r[2].m128_f32[2];
            ��ɫ����2.r[2].m128_f32[0] = -��ɫ����.r[0].m128_f32[0]; ��ɫ����2.r[2].m128_f32[1] = ��ɫ����.r[0].m128_f32[1];
            ��ɫ����2.r[2].m128_f32[2] = ��ɫ����.r[0].m128_f32[2];

            ��ɫ����.r[3].m128_f32[0] = ����λ��.m128_f32[0]; ��ɫ����.r[3].m128_f32[1] = ����λ��.m128_f32[1];
            ��ɫ����.r[3].m128_f32[2] = ����λ��.m128_f32[2];

            ����->��ɫ����.insert(pair<wstring, XMMATRIX>(��������, ��ɫ����));

            l�ڵ�id = FbxCharacter::ENodeId(int(l�ڵ�id) + 1);
        }
    }

    �󶨾��� = XMMatrixIdentity();
    ����->��ɫ����.insert(pair<wstring, XMMATRIX>(L"���ڵ�", �󶨾���));
}

void C��̬����::���ع���λ����Ϣ()
{
    int i = 0;
    int j = 0;
    XMFLOAT3 �ڵ�λ��{};
    XMMATRIX ������� = XMMatrixIdentity();

    for (i = 0; i < m���ڵ�->�ӽڵ�����; i++)
    {
        for (j = 0; j < m��������.size(); j++)
        {
            if (m��������[j] == m���ڵ�->�ӽڵ�[i].�ڵ�����)
            {
                m���ڵ�->�ӽڵ�[i].ԭʼλ�� = m���ڵ�->�ӽڵ�[i].�任.λ��;
                ���ع���λ����Ϣ(&m���ڵ�->�ӽڵ�[i], �������);
            }
        }
    }
}

void C��̬����::���ع���λ����Ϣ(S�任�ڵ�* p�ڵ�, XMMATRIX �������)
{
    int i = 0;
    int j = 0;
    int k = 0;
    SSRT�任 �任;
    XMVECTOR λ��{};
    XMVECTOR ��ת{};
    XMMATRIX �任����{};
    XMMATRIX ������ת{};

    wstring �������� = p�ڵ�->�ڵ�����;
    ������ת = �������;

    �任.���� = p�ڵ�->�任.����;
    �任.��ת.x = p�ڵ�->���ڵ�->�任.��ת.x;
    �任.��ת.y = p�ڵ�->���ڵ�->�任.��ת.y;
    �任.��ת.z = p�ڵ�->���ڵ�->�任.��ת.z;
    �任���� = XMMatrixRotationRollPitchYaw(�任.��ת.x * XM_PI / 180,
        �任.��ת.y * XM_PI / 180, �任.��ת.z * XM_PI / 180);
    p�ڵ�->ԭʼλ�� = p�ڵ�->�任.λ��;
    �任.��ת.x = p�ڵ�->�任.��ת.x;
    �任.��ת.y = p�ڵ�->�任.��ת.y;
    �任.��ת.z = p�ڵ�->�任.��ת.z;
    p�ڵ�->ԭʼ��ת = �任.��ת;
    ������ת = �任���� * �������;
    p�ڵ�->������� = ������ת;
    λ��.m128_f32[0] = p�ڵ�->�任.λ��.x;
    λ��.m128_f32[1] = p�ڵ�->�任.λ��.y;
    λ��.m128_f32[2] = p�ڵ�->�任.λ��.z;
    λ�� = XMVector3TransformCoord(λ��, ������ת);
    λ��.m128_f32[0] += p�ڵ�->���ڵ�->�任.λ��.x;
    λ��.m128_f32[1] += p�ڵ�->���ڵ�->�任.λ��.y;
    λ��.m128_f32[2] += p�ڵ�->���ڵ�->�任.λ��.z;
    �任.λ��.x = λ��.m128_f32[0];
    �任.λ��.y = λ��.m128_f32[1];
    �任.λ��.z = λ��.m128_f32[2];
    XMStoreFloat3(&�任.λ��, λ��);
    �任.��ת = p�ڵ�->�任.��ת;
    p�ڵ�->�任.λ��.x = �任.λ��.x;
    p�ڵ�->�任.λ��.y = �任.λ��.y;
    p�ڵ�->�任.λ��.z = �任.λ��.z;

    for (j = 0; j < m�����任.size(); j++)
    {
        if (m��������[j] == p�ڵ�->�ڵ�����)
        {
            m�����任[j].SRT�任.λ�� = �任.λ��;
            XMStoreFloat3x3(&m�����任[j].��ת, ������ת);
        }
    }

    for(i = 0; i < p�ڵ�->�ӽڵ�����; i++)
        ���ع���λ����Ϣ(&p�ڵ�->�ӽڵ�[i], ������ת);
}

void C��̬����::����������(wstring ��������, S�任�ڵ�*& Ŀ��ڵ�)
{
    int i = 0;

    for (i = 0; i < m���ڵ�->�ӽڵ�����; i++)
    {
        ����������(&m���ڵ�->�ӽڵ�[i], ��������, Ŀ��ڵ�);
    }
}

void C��̬����::����������(S�任�ڵ�* �任�ڵ�, wstring ��������, S�任�ڵ�*& Ŀ��ڵ�)
{
    int i = 0;

    if (�任�ڵ�->�ڵ����� == ��������)
    {
        Ŀ��ڵ� = �任�ڵ�;
        return;
    }

    for (i = 0; i < �任�ڵ�->�ӽڵ�����; i++)
    {
        ����������(&�任�ڵ�->�ӽڵ�[i], ��������, Ŀ��ڵ�);
    }
}

void C��̬����::�趨�����(S�任�ڵ�* �任�ڵ�, UINT �����)
{
    �任�ڵ�->�������.resize(�����);

    for (int i = 0; i < �任�ڵ�->�ӽڵ�����; i++)
    {
        �趨�����(&�任�ڵ�->�ӽڵ�[i], �����);
    }
}

void C��̬����::�趨֡��(S�任�ڵ�* �任�ڵ�, UINT ���, UINT ֡��)
{
    �任�ڵ�->�������[���].֡.resize(֡��);

    for (int i = 0; i < �任�ڵ�->�ӽڵ�����; i++)
    {
        �趨֡��(&�任�ڵ�->�ӽڵ�[i], ���, ֡��);
    }
}

void C��̬����::�ϲ����嶯����Ϣ()
{
    UINT i = 0;
    UINT j = 0;
    UINT k = 0;
    UINT m = 0;
    UINT n = 0;
    UINT u = 0;
    UINT v = 0;
    UINT w = 0;
    int x, y = 0;
    XMMATRIX �任���� = XMMatrixIdentity();
    XMMATRIX �任����2 = XMMatrixIdentity();
    XMMATRIX ��ת�任 = XMMatrixIdentity();
    XMVECTOR l��ת����{};
    XMVECTOR l��ת����2{};
    XMVECTOR λ��{};
    XMVECTOR ��ת{};
    XMVECTOR ����{};
    XMFLOAT3X3 ��ת����{};
    XMFLOAT4X3 ��ʼ����{};
    float l֡���� = 0;
    float l�仯�� = 0;
    UINT l��ǰ������� = 0;
    S�任�ڵ�* �����ڵ�;
    UINT ֡ƫ�� = 0;
    bool �Ƿ�Ϊ����� = false;

    XMStoreFloat4x3(&��ʼ����, XMMatrixIdentity());

    �������.resize(m��������->Ƭ��.size());
    for (i = 0; i < �������.size(); i++)
    {
        �������[i].ԭʼʱ�� = (float)(m��������->Ƭ��[i].����֡ - m��������->Ƭ��[i].��ʼ֡ + 1) / m��������->Ƭ��[i].֡����;
        �������[i].֡.resize(m��������->Ƭ��[i].����֡ - m��������->Ƭ��[i].��ʼ֡ + 1);
        �������[i].�Ƿ�ѭ�� = 1;
        �������[i].������� = m��������->Ƭ��[i].Ƭ������;
        �������[i].�ٶ� = 1.0f;
        ֡ƫ�� = m��������->Ƭ��[i].��ʼ֡;

        �趨�����(m���ڵ�, m��������->Ƭ��.size());
        �趨֡��(m���ڵ�, i, �������[i].֡.size());

        for (j = ֡ƫ��; j < �������[i].֡.size() + ֡ƫ��; j++)
        {
            �������[i].֡[j - ֡ƫ��].�����任.resize(��������, ��ʼ����);
            �������[i].֡[j - ֡ƫ��].����任.resize(����->Ԫ��.size(), ��ʼ����);

            for (k = 0; k < m��������->Ƭ��[i].������.size(); k++)
            {
                for (m = 0; m < m��������->Ƭ��[i].������[k].����.size(); m++)
                {
                    //��������任
                    for (n = 0; n < ����->Ԫ��.size(); n++)
                    {
                        if (m��������->Ƭ��[i].������[k].����[m].��������.compare(����->Ԫ��[n]->��������) == 0)
                        {
                            if (m��������->Ƭ��[i].������[k].����[m].λ��.size() == 0)
                            {
                                �Ƿ�Ϊ����� = true;
                                for (x = 0; x < 4; x++)
                                    for (y = 0; y < 4; y++)
                                        if (����->������[����->Ԫ��[n]->��������].r[x].m128_f32[y] != 0.0f) �Ƿ�Ϊ����� = false;
                                if (�Ƿ�Ϊ�����)
                                    XMStoreFloat4x3(&�������[i].֡[j - ֡ƫ��].����任[n], ����->Ԫ��[n]->�任);
                                else
                                    XMStoreFloat4x3(&�������[i].֡[j - ֡ƫ��].����任[n], ����->������[����->Ԫ��[n]->��������]);
                            }

                            //λ�ñ任
                            //��֡ǰ��ǰ֡��
                            if (m��������->Ƭ��[i].������[k].����[m].λ��.size() != 0)
                                if (m��������->Ƭ��[i].������[k].����[m].λ��[0].֡�� >= j)
                                {
                                    �������[i].֡[j - ֡ƫ��].����任[n].m[3][2] = m��������->Ƭ��[i].������[k].����[m].λ��[0].λ��.x;
                                    �������[i].֡[j - ֡ƫ��].����任[n].m[3][1] = m��������->Ƭ��[i].������[k].����[m].λ��[0].λ��.y;
                                    �������[i].֡[j - ֡ƫ��].����任[n].m[3][0] = m��������->Ƭ��[i].������[k].����[m].λ��[0].λ��.z;
                                }

                            for (u = 0; u < m��������->Ƭ��[i].������[k].����[m].λ��.size(); u++)
                            {
                                //��֡������
                                if (u + 1 < m��������->Ƭ��[i].������[k].����[m].λ��.size())
                                    if (m��������->Ƭ��[i].������[k].����[m].λ��[u].֡�� <= j &&
                                        m��������->Ƭ��[i].������[k].����[m].λ��[u + 1].֡�� > j)
                                    {
                                        l֡���� = ((float)j - m��������->Ƭ��[i].������[k].����[m].λ��[u].֡��) /
                                            (m��������->Ƭ��[i].������[k].����[m].λ��[u + 1].֡�� -
                                                m��������->Ƭ��[i].������[k].����[m].λ��[u].֡��);
                                        λ��.m128_f32[2] = (m��������->Ƭ��[i].������[k].����[m].λ��[u + 1].λ��.x -
                                            m��������->Ƭ��[i].������[k].����[m].λ��[u].λ��.x) * l֡���� +
                                            m��������->Ƭ��[i].������[k].����[m].λ��[u].λ��.x;
                                        λ��.m128_f32[1] = (m��������->Ƭ��[i].������[k].����[m].λ��[u + 1].λ��.y -
                                            m��������->Ƭ��[i].������[k].����[m].λ��[u].λ��.y) * l֡���� +
                                            m��������->Ƭ��[i].������[k].����[m].λ��[u].λ��.y;
                                        λ��.m128_f32[0] = -((m��������->Ƭ��[i].������[k].����[m].λ��[u + 1].λ��.z -
                                            m��������->Ƭ��[i].������[k].����[m].λ��[u].λ��.z) * l֡���� +
                                            m��������->Ƭ��[i].������[k].����[m].λ��[u].λ��.z);

                                        �������[i].֡[j - ֡ƫ��].����任[n].m[3][0] = λ��.m128_f32[0];
                                        �������[i].֡[j - ֡ƫ��].����任[n].m[3][1] = λ��.m128_f32[1];
                                        �������[i].֡[j - ֡ƫ��].����任[n].m[3][2] = λ��.m128_f32[2];
                                    }
                            }

                            //��֡�������֡��
                            if (m��������->Ƭ��[i].������[k].����[m].λ��.size() > 0)
                                if (m��������->Ƭ��[i].������[k].����[m].λ��[m��������->Ƭ��[i].������[k].����[m].λ��.size() - 1].֡�� <= j)
                                {
                                    λ��.m128_f32[2] = m��������->Ƭ��[i].������[k].����[m].λ��[
                                        m��������->Ƭ��[i].������[k].����[m].λ��.size() - 1].λ��.x;
                                    λ��.m128_f32[1] = m��������->Ƭ��[i].������[k].����[m].λ��[
                                        m��������->Ƭ��[i].������[k].����[m].λ��.size() - 1].λ��.y;
                                    λ��.m128_f32[0] = -m��������->Ƭ��[i].������[k].����[m].λ��[
                                        m��������->Ƭ��[i].������[k].����[m].λ��.size() - 1].λ��.z;

                                    �������[i].֡[j - ֡ƫ��].����任[n].m[3][0] = λ��.m128_f32[0];
                                    �������[i].֡[j - ֡ƫ��].����任[n].m[3][1] = λ��.m128_f32[1];
                                    �������[i].֡[j - ֡ƫ��].����任[n].m[3][2] = λ��.m128_f32[2];
                                }

                            //��ת�任
                            if (m��������->Ƭ��[i].������[k].����[m].��ת.size() == 0)
                            {
                                �Ƿ�Ϊ����� = true;
                                for (x = 0; x < 4; x++)
                                    for (y = 0; y < 4; y++)
                                        if (����->������[����->Ԫ��[n]->��������].r[x].m128_f32[y] != 0.0f) �Ƿ�Ϊ����� = false;
                                if (�Ƿ�Ϊ�����)
                                    XMStoreFloat4x3(&�������[i].֡[j - ֡ƫ��].����任[n], ����->Ԫ��[n]->�任);
                                else
                                XMStoreFloat4x3(&�������[i].֡[j - ֡ƫ��].����任[n], ����->������[����->Ԫ��[n]->��������]);
                            }

                            //��֡ǰ��֡��
                            if (m��������->Ƭ��[i].������[k].����[m].��ת.size() != 0)
                                if (m��������->Ƭ��[i].������[k].����[m].��ת[0].֡�� >= j)
                                {
                                    ��ת.m128_f32[0] = m��������->Ƭ��[i].������[k].����[m].��ת[0].��ת.x * XM_PI / 180;
                                    ��ת.m128_f32[1] = m��������->Ƭ��[i].������[k].����[m].��ת[0].��ת.y * XM_PI / 180;
                                    ��ת.m128_f32[2] = m��������->Ƭ��[i].������[k].����[m].��ת[0].��ת.z * XM_PI / 180;

                                    ��ת�任 = XMMatrixRotationRollPitchYaw(��ת.m128_f32[1], ��ת.m128_f32[2], ��ת.m128_f32[0]);

                                    �������[i].֡[j - ֡ƫ��].����任[n].m[0][0] = ��ת�任.r[0].m128_f32[0];
                                    �������[i].֡[j - ֡ƫ��].����任[n].m[0][1] = ��ת�任.r[0].m128_f32[1];
                                    �������[i].֡[j - ֡ƫ��].����任[n].m[0][2] = ��ת�任.r[0].m128_f32[2];
                                    �������[i].֡[j - ֡ƫ��].����任[n].m[1][0] = ��ת�任.r[1].m128_f32[0];
                                    �������[i].֡[j - ֡ƫ��].����任[n].m[1][1] = ��ת�任.r[1].m128_f32[1];
                                    �������[i].֡[j - ֡ƫ��].����任[n].m[1][2] = ��ת�任.r[1].m128_f32[2];
                                    �������[i].֡[j - ֡ƫ��].����任[n].m[2][0] = ��ת�任.r[2].m128_f32[0];
                                    �������[i].֡[j - ֡ƫ��].����任[n].m[2][1] = ��ת�任.r[2].m128_f32[1];
                                    �������[i].֡[j - ֡ƫ��].����任[n].m[2][2] = ��ת�任.r[2].m128_f32[2];
                                }

                            for (u = 0; u < m��������->Ƭ��[i].������[k].����[m].��ת.size(); u++)
                            {
                                //��֡������
                                if (u + 1 < m��������->Ƭ��[i].������[k].����[m].��ת.size())
                                    if (m��������->Ƭ��[i].������[k].����[m].��ת[u].֡�� <= j && m��������->Ƭ��[i].������[k].����[m].��ת[u + 1].֡�� > j)
                                    {
                                        l֡���� = ((float)j - m��������->Ƭ��[i].������[k].����[m].��ת[u].֡��) /
                                            (m��������->Ƭ��[i].������[k].����[m].��ת[u + 1].֡�� -
                                                m��������->Ƭ��[i].������[k].����[m].��ת[u].֡��);

                                        l��ת����.m128_f32[0] = m��������->Ƭ��[i].������[k].����[m].��ת[u].��ת.x;
                                        l��ת����.m128_f32[1] = m��������->Ƭ��[i].������[k].����[m].��ת[u].��ת.y;
                                        l��ת����.m128_f32[2] = m��������->Ƭ��[i].������[k].����[m].��ת[u].��ת.z;
                                        l��ת����2.m128_f32[0] = m��������->Ƭ��[i].������[k].����[m].��ת[u + 1].��ת.x;
                                        l��ת����2.m128_f32[1] = m��������->Ƭ��[i].������[k].����[m].��ת[u + 1].��ת.y;
                                        l��ת����2.m128_f32[2] = m��������->Ƭ��[i].������[k].����[m].��ת[u + 1].��ת.z;

                                        l��ת���� = (l��ת����2 - l��ת����) * l֡���� + l��ת����;

                                        ��ת.m128_f32[0] = l��ת����.m128_f32[0] * XM_PI / 180;
                                        ��ת.m128_f32[1] = l��ת����.m128_f32[1] * XM_PI / 180;
                                        ��ת.m128_f32[2] = l��ת����.m128_f32[2] * XM_PI / 180;
                                        ��ת�任 = XMMatrixRotationRollPitchYaw(��ת.m128_f32[1], ��ת.m128_f32[2], ��ת.m128_f32[0]);

                                        �������[i].֡[j - ֡ƫ��].����任[n].m[0][0] = ��ת�任.r[0].m128_f32[0];
                                        �������[i].֡[j - ֡ƫ��].����任[n].m[0][1] = ��ת�任.r[0].m128_f32[1];
                                        �������[i].֡[j - ֡ƫ��].����任[n].m[0][2] = ��ת�任.r[0].m128_f32[2];
                                        �������[i].֡[j - ֡ƫ��].����任[n].m[1][0] = ��ת�任.r[1].m128_f32[0];
                                        �������[i].֡[j - ֡ƫ��].����任[n].m[1][1] = ��ת�任.r[1].m128_f32[1];
                                        �������[i].֡[j - ֡ƫ��].����任[n].m[1][2] = ��ת�任.r[1].m128_f32[2];
                                        �������[i].֡[j - ֡ƫ��].����任[n].m[2][0] = ��ת�任.r[2].m128_f32[0];
                                        �������[i].֡[j - ֡ƫ��].����任[n].m[2][1] = ��ת�任.r[2].m128_f32[1];
                                        �������[i].֡[j - ֡ƫ��].����任[n].m[2][2] = ��ת�任.r[2].m128_f32[2];
                                    }
                            }

                            //��֡�����
                            if (m��������->Ƭ��[i].������[k].����[m].��ת.size() > 0)
                                if (m��������->Ƭ��[i].������[k].����[m].��ת[m��������->Ƭ��[i].������[k].����[m].��ת.size() - 1].֡�� <= j)
                                {
                                    ��ת.m128_f32[0] = XM_PI / 180 * m��������->Ƭ��[i].������[k].����[m].��ת[
                                        m��������->Ƭ��[i].������[k].����[m].��ת.size() - 1].��ת.x;
                                    ��ת.m128_f32[1] = XM_PI / 180 * m��������->Ƭ��[i].������[k].����[m].��ת[
                                        m��������->Ƭ��[i].������[k].����[m].��ת.size() - 1].��ת.y;
                                    ��ת.m128_f32[2] = XM_PI / 180 * m��������->Ƭ��[i].������[k].����[m].��ת[
                                        m��������->Ƭ��[i].������[k].����[m].��ת.size() - 1].��ת.z;

                                    ��ת�任 = XMMatrixRotationRollPitchYaw(��ת.m128_f32[1], ��ת.m128_f32[2], ��ת.m128_f32[0]);

                                    �������[i].֡[j - ֡ƫ��].����任[n].m[0][0] = ��ת�任.r[0].m128_f32[0];
                                    �������[i].֡[j - ֡ƫ��].����任[n].m[0][1] = ��ת�任.r[0].m128_f32[1];
                                    �������[i].֡[j - ֡ƫ��].����任[n].m[0][2] = ��ת�任.r[0].m128_f32[2];
                                    �������[i].֡[j - ֡ƫ��].����任[n].m[1][0] = ��ת�任.r[1].m128_f32[0];
                                    �������[i].֡[j - ֡ƫ��].����任[n].m[1][1] = ��ת�任.r[1].m128_f32[1];
                                    �������[i].֡[j - ֡ƫ��].����任[n].m[1][2] = ��ת�任.r[1].m128_f32[2];
                                    �������[i].֡[j - ֡ƫ��].����任[n].m[2][0] = ��ת�任.r[2].m128_f32[0];
                                    �������[i].֡[j - ֡ƫ��].����任[n].m[2][1] = ��ת�任.r[2].m128_f32[1];
                                    �������[i].֡[j - ֡ƫ��].����任[n].m[2][2] = ��ת�任.r[2].m128_f32[2];
                                }

                            //���ű任
                            if (m��������->Ƭ��[i].������[k].����[m].����.size() == 0)
                            {
                                �Ƿ�Ϊ����� = true;
                                for (x = 0; x < 4; x++)
                                    for (y = 0; y < 4; y++)
                                        if (����->������[����->Ԫ��[n]->��������].r[x].m128_f32[y] != 0.0f) �Ƿ�Ϊ����� = false;
                                if (�Ƿ�Ϊ�����)
                                    XMStoreFloat4x3(&�������[i].֡[j - ֡ƫ��].����任[n], ����->Ԫ��[n]->�任);
                                else
                                    XMStoreFloat4x3(&�������[i].֡[j - ֡ƫ��].����任[n], ����->������[����->Ԫ��[n]->��������]);
                            }
                            // 
                            //��֡ǰ��ǰ֡��
                            if (m��������->Ƭ��[i].������[k].����[m].����.size() != 0)
                                if (m��������->Ƭ��[i].������[k].����[m].����[m��������->Ƭ��[i].������[k].����[m].����.size() - 1].֡�� >= j)
                                {
                                    ����.m128_f32[0] = m��������->Ƭ��[i].������[k].����[m].����[0].����.x;
                                    ����.m128_f32[1] = m��������->Ƭ��[i].������[k].����[m].����[0].����.y;
                                    ����.m128_f32[2] = m��������->Ƭ��[i].������[k].����[m].����[0].����.z;

                                    �任���� = XMMatrixScaling(����.m128_f32[1], ����.m128_f32[0], ����.m128_f32[2]);
                                    �任����2 = XMLoadFloat4x3(&�������[i].֡[j - ֡ƫ��].����任[n]);
                                    �任���� *= �任����2;

                                    �������[i].֡[j - ֡ƫ��].����任[n].m[0][0] = �任����.r[0].m128_f32[0];
                                    �������[i].֡[j - ֡ƫ��].����任[n].m[0][1] = �任����.r[0].m128_f32[1];
                                    �������[i].֡[j - ֡ƫ��].����任[n].m[0][2] = �任����.r[0].m128_f32[2];
                                    �������[i].֡[j - ֡ƫ��].����任[n].m[1][0] = �任����.r[1].m128_f32[0];
                                    �������[i].֡[j - ֡ƫ��].����任[n].m[1][1] = �任����.r[1].m128_f32[1];
                                    �������[i].֡[j - ֡ƫ��].����任[n].m[1][2] = �任����.r[1].m128_f32[2];
                                    �������[i].֡[j - ֡ƫ��].����任[n].m[2][0] = �任����.r[2].m128_f32[0];
                                    �������[i].֡[j - ֡ƫ��].����任[n].m[2][1] = �任����.r[2].m128_f32[1];
                                    �������[i].֡[j - ֡ƫ��].����任[n].m[2][2] = �任����.r[2].m128_f32[2];
                                }

                            for (u = 0; u < m��������->Ƭ��[i].������[k].����[m].����.size(); u++)
                            {

                                //��֡������
                                if (u + 1 < m��������->Ƭ��[i].������[k].����[m].����.size())
                                    if (m��������->Ƭ��[i].������[k].����[m].����[u].֡�� <= j &&
                                        m��������->Ƭ��[i].������[k].����[m].����[u + 1].֡�� > j)
                                    {
                                        l֡���� = ((float)j - m��������->Ƭ��[i].������[k].����[m].����[u].֡��) /
                                            (m��������->Ƭ��[i].������[k].����[m].����[u + 1].֡�� -
                                                m��������->Ƭ��[i].������[k].����[m].����[u].֡��);
                                        ����.m128_f32[0] = (m��������->Ƭ��[i].������[k].����[m].����[u + 1].����.x -
                                            m��������->Ƭ��[i].������[k].����[m].����[u].����.x) * l֡���� +
                                            m��������->Ƭ��[i].������[k].����[m].����[u].����.x;
                                        ����.m128_f32[1] = (m��������->Ƭ��[i].������[k].����[m].����[u + 1].����.y -
                                            m��������->Ƭ��[i].������[k].����[m].����[u].����.y) * l֡���� +
                                            m��������->Ƭ��[i].������[k].����[m].����[u].����.y;
                                        ����.m128_f32[2] = (m��������->Ƭ��[i].������[k].����[m].����[u + 1].����.z -
                                            m��������->Ƭ��[i].������[k].����[m].����[u].����.z) * l֡���� +
                                            m��������->Ƭ��[i].������[k].����[m].����[u].����.z;

                                        �任���� = XMMatrixScaling(����.m128_f32[1], ����.m128_f32[0], ����.m128_f32[2]);
                                        �任����2 = XMLoadFloat4x3(&�������[i].֡[j - ֡ƫ��].����任[n]);
                                        �任���� *= �任����2;

                                        �������[i].֡[j - ֡ƫ��].����任[n].m[0][0] = �任����.r[0].m128_f32[0];
                                        �������[i].֡[j - ֡ƫ��].����任[n].m[0][1] = �任����.r[0].m128_f32[1];
                                        �������[i].֡[j - ֡ƫ��].����任[n].m[0][2] = �任����.r[0].m128_f32[2];
                                        �������[i].֡[j - ֡ƫ��].����任[n].m[1][0] = �任����.r[1].m128_f32[0];
                                        �������[i].֡[j - ֡ƫ��].����任[n].m[1][1] = �任����.r[1].m128_f32[1];
                                        �������[i].֡[j - ֡ƫ��].����任[n].m[1][2] = �任����.r[1].m128_f32[2];
                                        �������[i].֡[j - ֡ƫ��].����任[n].m[2][0] = �任����.r[2].m128_f32[0];
                                        �������[i].֡[j - ֡ƫ��].����任[n].m[2][1] = �任����.r[2].m128_f32[1];
                                        �������[i].֡[j - ֡ƫ��].����任[n].m[2][2] = �任����.r[2].m128_f32[2];
                                    }
                            }

                            //��֡�����
                            if (m��������->Ƭ��[i].������[k].����[m].����.size() > 0)
                                if (m��������->Ƭ��[i].������[k].����[m].����[m��������->Ƭ��[i].������[k].����[m].����.size() - 1].֡�� <= j)
                                {
                                    ����.m128_f32[0] = m��������->Ƭ��[i].������[k].����[m].����[
                                        m��������->Ƭ��[i].������[k].����[m].����.size() - 1].����.x;
                                    ����.m128_f32[1] = m��������->Ƭ��[i].������[k].����[m].����[
                                        m��������->Ƭ��[i].������[k].����[m].����.size() - 1].����.y;
                                    ����.m128_f32[2] = m��������->Ƭ��[i].������[k].����[m].����[
                                        m��������->Ƭ��[i].������[k].����[m].����.size() - 1].����.z;

                                    �任���� = XMMatrixScaling(����.m128_f32[1], ����.m128_f32[0], ����.m128_f32[2]);
                                    �任����2 = XMLoadFloat4x3(&�������[i].֡[j - ֡ƫ��].����任[n]);
                                    �任���� *= �任����2;

                                    �������[i].֡[j - ֡ƫ��].����任[n].m[0][0] = �任����.r[0].m128_f32[0];
                                    �������[i].֡[j - ֡ƫ��].����任[n].m[0][1] = �任����.r[0].m128_f32[1];
                                    �������[i].֡[j - ֡ƫ��].����任[n].m[0][2] = �任����.r[0].m128_f32[2];
                                    �������[i].֡[j - ֡ƫ��].����任[n].m[1][0] = �任����.r[1].m128_f32[0];
                                    �������[i].֡[j - ֡ƫ��].����任[n].m[1][1] = �任����.r[1].m128_f32[1];
                                    �������[i].֡[j - ֡ƫ��].����任[n].m[1][2] = �任����.r[1].m128_f32[2];
                                    �������[i].֡[j - ֡ƫ��].����任[n].m[2][0] = �任����.r[2].m128_f32[0];
                                    �������[i].֡[j - ֡ƫ��].����任[n].m[2][1] = �任����.r[2].m128_f32[1];
                                    �������[i].֡[j - ֡ƫ��].����任[n].m[2][2] = �任����.r[2].m128_f32[2];
                                }
                        }
                    }

                    //���ع����任
                    for (n = 1; n < ��������; n++)
                    {
                        if (m��������[n].compare(m��������->Ƭ��[i].������[k].����[m].��������) == 0)
                        {
                            ����������(m��������[n], �����ڵ�);

                            for (w = 0; w < m��Ƥ����->��������.size(); w++)
                            {
                                for (v = 0; v < m��Ƥ����->��������[w].����.size(); v++)
                                {
                                    if (m��Ƥ����->��������[w].����[v].�������� == m��������[n])
                                    {
                                        ����������(m��������[n], �����ڵ�);
                                        XMStoreFloat3x3(&�����ڵ�->��ʼ������ת, m��Ƥ����->��������[w].����[v].����������ת����);
                                        �����ڵ�->��ʼ����λ��.x = m��Ƥ����->��������[w].����[v].����������ת����.r[3].m128_f32[0];
                                        �����ڵ�->��ʼ����λ��.y = m��Ƥ����->��������[w].����[v].����������ת����.r[3].m128_f32[1];
                                        �����ڵ�->��ʼ����λ��.z = m��Ƥ����->��������[w].����[v].����������ת����.r[3].m128_f32[2];
                                        goto ����5;
                                    }
                                }
                            }
                            ����5: if (0);

                            //λ�ñ任
                            if (m��������->Ƭ��[i].������[k].����[m].λ��.size() == 0)
                            {
                                �Ƿ�Ϊ����� = true;
                                for (x = 0; x < 4; x++)
                                    for (y = 0; y < 4; y++)
                                        if (����->������[m��������[n]].r[x].m128_f32[y] != 0.0f) �Ƿ�Ϊ����� = false;
                                if (�Ƿ�Ϊ�����)
                                {
                                    �����ڵ�->�������[i].֡[j - ֡ƫ��].�任.λ�� = �����ڵ�->ԭʼλ��;
                                }
                                else
                                {
                                    �����ڵ�->�������[i].֡[j - ֡ƫ��].�任.λ��.x = ����->������[m��������[n]].r[3].m128_f32[0];
                                    �����ڵ�->�������[i].֡[j - ֡ƫ��].�任.λ��.y = ����->������[m��������[n]].r[3].m128_f32[1];
                                    �����ڵ�->�������[i].֡[j - ֡ƫ��].�任.λ��.z = ����->������[m��������[n]].r[3].m128_f32[2];
                                }

                            }

                            //��֡ǰ��ǰ֡��
                            if (m��������->Ƭ��[i].������[k].����[m].λ��.size() != 0)
                                if (m��������->Ƭ��[i].������[k].����[m].λ��[0].֡�� >= j)
                                {
                                    �����ڵ�->�������[i].֡[j - ֡ƫ��].�任.λ��.z = m��������->Ƭ��[i].������[k].����[m].λ��[0].λ��.x;
                                    �����ڵ�->�������[i].֡[j - ֡ƫ��].�任.λ��.y = m��������->Ƭ��[i].������[k].����[m].λ��[0].λ��.y;
                                    �����ڵ�->�������[i].֡[j - ֡ƫ��].�任.λ��.x = -m��������->Ƭ��[i].������[k].����[m].λ��[0].λ��.z;
                                }

                            for (u = 0; u < m��������->Ƭ��[i].������[k].����[m].λ��.size(); u++)
                            {
                                //��֡������
                                if (u + 1 < m��������->Ƭ��[i].������[k].����[m].λ��.size())
                                    if (m��������->Ƭ��[i].������[k].����[m].λ��[u].֡�� <= j &&
                                        m��������->Ƭ��[i].������[k].����[m].λ��[u + 1].֡�� > j)
                                    {
                                        l֡���� = ((float)j - m��������->Ƭ��[i].������[k].����[m].λ��[u].֡��) /
                                            (m��������->Ƭ��[i].������[k].����[m].λ��[u + 1].֡�� -
                                                m��������->Ƭ��[i].������[k].����[m].λ��[u].֡��);

                                        �����ڵ�->�������[i].֡[j - ֡ƫ��].�任.λ��.z = (m��������->Ƭ��[i].������[k].����[m].λ��[u + 1].λ��.x -
                                            m��������->Ƭ��[i].������[k].����[m].λ��[u].λ��.x) * l֡���� +
                                            m��������->Ƭ��[i].������[k].����[m].λ��[u].λ��.x;
                                        �����ڵ�->�������[i].֡[j - ֡ƫ��].�任.λ��.y = (m��������->Ƭ��[i].������[k].����[m].λ��[u + 1].λ��.y -
                                            m��������->Ƭ��[i].������[k].����[m].λ��[u].λ��.y) * l֡���� +
                                            m��������->Ƭ��[i].������[k].����[m].λ��[u].λ��.y;
                                        �����ڵ�->�������[i].֡[j - ֡ƫ��].�任.λ��.x = -((m��������->Ƭ��[i].������[k].����[m].λ��[u + 1].λ��.z -
                                            m��������->Ƭ��[i].������[k].����[m].λ��[u].λ��.z) * l֡���� +
                                            m��������->Ƭ��[i].������[k].����[m].λ��[u].λ��.z);
                                    }
                            }

                            //��֡�������֡��
                            if (m��������->Ƭ��[i].������[k].����[m].λ��.size() > 0)
                                if (m��������->Ƭ��[i].������[k].����[m].λ��[m��������->Ƭ��[i].������[k].����[m].λ��.size() - 1].֡�� <= j)
                                {
                                    v = m��������->Ƭ��[i].������[k].����[m].λ��.size() - 1;
                                    �����ڵ�->�������[i].֡[j - ֡ƫ��].�任.λ��.z = m��������->Ƭ��[i].������[k].����[m].λ��[v].λ��.x;
                                    �����ڵ�->�������[i].֡[j - ֡ƫ��].�任.λ��.y = m��������->Ƭ��[i].������[k].����[m].λ��[v].λ��.y;
                                    �����ڵ�->�������[i].֡[j - ֡ƫ��].�任.λ��.x = -m��������->Ƭ��[i].������[k].����[m].λ��[v].λ��.z;
                                }

                            //��ת�任
                            if (m��������->Ƭ��[i].������[k].����[m].��ת.size() == 0)
                            {
                                �Ƿ�Ϊ����� = true;
                                for (x = 0; x < 4; x++)
                                    for (y = 0; y < 4; y++)
                                        if (����->������[m��������[n]].r[x].m128_f32[y] != 0.0f) �Ƿ�Ϊ����� = false;
                                if (�Ƿ�Ϊ�����)
                                {
                                    �����ڵ�->�������[i].֡[j - ֡ƫ��].�任.��ת = �����ڵ�->ԭʼ��ת;
                                    XMStoreFloat3x3(&�����ڵ�->�������[i].֡[j - ֡ƫ��].��ת, XMMatrixRotationRollPitchYaw(
                                        �����ڵ�->ԭʼ��ת.x * XM_PI / 180, �����ڵ�->ԭʼ��ת.y * XM_PI / 180, �����ڵ�->ԭʼ��ת.z * XM_PI / 180));
                                }
                                else
                                {
                                    XMStoreFloat3x3(&�����ڵ�->�������[i].֡[j - ֡ƫ��].��ת, ����->������[m��������[n]]);
                                } 
                            }

                            //��֡ǰ��֡��
                            if (m��������->Ƭ��[i].������[k].����[m].��ת.size() != 0)
                                if (m��������->Ƭ��[i].������[k].����[m].��ת[0].֡�� >= j)
                                {
                                    �����ڵ�->�������[i].֡[j - ֡ƫ��].�任.��ת.x = m��������->Ƭ��[i].������[k].����[m].��ת[0].��ת.y;
                                    �����ڵ�->�������[i].֡[j - ֡ƫ��].�任.��ת.y = m��������->Ƭ��[i].������[k].����[m].��ת[0].��ת.z;
                                    �����ڵ�->�������[i].֡[j - ֡ƫ��].�任.��ת.z = m��������->Ƭ��[i].������[k].����[m].��ת[0].��ת.x;
                                    XMStoreFloat3x3(&�����ڵ�->�������[i].֡[j - ֡ƫ��].��ת, XMMatrixRotationRollPitchYaw(
                                        m��������->Ƭ��[i].������[k].����[m].��ת[0].��ת.y * XM_PI / 180,
                                        m��������->Ƭ��[i].������[k].����[m].��ת[0].��ת.z * XM_PI / 180,
                                        m��������->Ƭ��[i].������[k].����[m].��ת[0].��ת.x * XM_PI / 180));
                                }

                            //��֡������
                            for (u = 0; u < m��������->Ƭ��[i].������[k].����[m].��ת.size(); u++)
                            {
                                if (u + 1 < m��������->Ƭ��[i].������[k].����[m].��ת.size())
                                    if (m��������->Ƭ��[i].������[k].����[m].��ת[u].֡�� <= j && m��������->Ƭ��[i].������[k].����[m].��ת[u + 1].֡�� > j)
                                    {
                                        l֡���� = ((float)j - m��������->Ƭ��[i].������[k].����[m].��ת[u].֡��) /
                                            (m��������->Ƭ��[i].������[k].����[m].��ת[u + 1].֡�� -
                                                m��������->Ƭ��[i].������[k].����[m].��ת[u].֡��);

                                        l��ת����.m128_f32[0] = m��������->Ƭ��[i].������[k].����[m].��ת[u].��ת.x;
                                        l��ת����.m128_f32[1] = m��������->Ƭ��[i].������[k].����[m].��ת[u].��ת.y;
                                        l��ת����.m128_f32[2] = m��������->Ƭ��[i].������[k].����[m].��ת[u].��ת.z;
                                        l��ת����2.m128_f32[0] = m��������->Ƭ��[i].������[k].����[m].��ת[u + 1].��ת.x;
                                        l��ת����2.m128_f32[1] = m��������->Ƭ��[i].������[k].����[m].��ת[u + 1].��ת.y;
                                        l��ת����2.m128_f32[2] = m��������->Ƭ��[i].������[k].����[m].��ת[u + 1].��ת.z;

                                        l��ת���� = (l��ת����2 - l��ת����) * l֡���� + l��ת����;

                                        �����ڵ�->�������[i].֡[j - ֡ƫ��].�任.��ת.z = l��ת����.m128_f32[0];
                                        �����ڵ�->�������[i].֡[j - ֡ƫ��].�任.��ת.x = l��ת����.m128_f32[1];
                                        �����ڵ�->�������[i].֡[j - ֡ƫ��].�任.��ת.y = l��ת����.m128_f32[2];
                                        XMStoreFloat3x3(&�����ڵ�->�������[i].֡[j - ֡ƫ��].��ת, XMMatrixRotationRollPitchYaw(
                                            l��ת����.m128_f32[1] * XM_PI / 180, l��ת����.m128_f32[2] * XM_PI / 180,
                                            l��ת����.m128_f32[0] * XM_PI / 180));
                                    }
                            }

                            //��֡�����
                            if (m��������->Ƭ��[i].������[k].����[m].��ת.size() > 0)
                                if (m��������->Ƭ��[i].������[k].����[m].��ת[m��������->Ƭ��[i].������[k].����[m].��ת.size() - 1].֡�� <= j)
                                {
                                    u = m��������->Ƭ��[i].������[k].����[m].��ת.size() - 1;
                                    �����ڵ�->�������[i].֡[j - ֡ƫ��].�任.��ת.z = m��������->Ƭ��[i].������[k].����[m].��ת[u].��ת.x;
                                    �����ڵ�->�������[i].֡[j - ֡ƫ��].�任.��ת.x = m��������->Ƭ��[i].������[k].����[m].��ת[u].��ת.y;
                                    �����ڵ�->�������[i].֡[j - ֡ƫ��].�任.��ת.y = m��������->Ƭ��[i].������[k].����[m].��ת[u].��ת.z;
                                    XMStoreFloat3x3(&�����ڵ�->�������[i].֡[j - ֡ƫ��].��ת, XMMatrixRotationRollPitchYaw(
                                        m��������->Ƭ��[i].������[k].����[m].��ת[u].��ת.y * XM_PI / 180, 
                                        m��������->Ƭ��[i].������[k].����[m].��ת[u].��ת.z * XM_PI / 180,
                                        m��������->Ƭ��[i].������[k].����[m].��ת[u].��ת.x * XM_PI / 180));
                                }

                            //���ű任
                            if (m��������->Ƭ��[i].������[k].����[m].����.size() == 0)
                            {
                                �����ڵ�->�������[i].֡[j - ֡ƫ��].�任.���� = XMFLOAT3{ 1.0f, 1.0f, 1.0f };
                            }

                            //��֡ǰ��ǰ֡��
                            if (m��������->Ƭ��[i].������[k].����[m].����.size() != 0)
                                if (m��������->Ƭ��[i].������[k].����[m].����[m��������->Ƭ��[i].������[k].����[m].����.size() - 1].֡�� >= j)
                                {
                                    �����ڵ�->�������[i].֡[j - ֡ƫ��].�任.����.z =
                                        m��������->Ƭ��[i].������[k].����[m].����[0].����.x;
                                    �����ڵ�->�������[i].֡[j - ֡ƫ��].�任.����.x =
                                        m��������->Ƭ��[i].������[k].����[m].����[0].����.y;
                                    �����ڵ�->�������[i].֡[j - ֡ƫ��].�任.����.y =
                                        m��������->Ƭ��[i].������[k].����[m].����[0].����.z;
                                }

                            for (u = 0; u < m��������->Ƭ��[i].������[k].����[m].����.size(); u++)
                            {
                                //��֡������
                                if (u + 1 < m��������->Ƭ��[i].������[k].����[m].����.size())
                                    if (m��������->Ƭ��[i].������[k].����[m].����[u].֡�� <= j &&
                                        m��������->Ƭ��[i].������[k].����[m].����[u + 1].֡�� > j)
                                    {
                                        l֡���� = ((float)j - m��������->Ƭ��[i].������[k].����[m].����[u].֡��) /
                                            (m��������->Ƭ��[i].������[k].����[m].����[u + 1].֡�� -
                                                m��������->Ƭ��[i].������[k].����[m].����[u].֡��);
                                        �����ڵ�->�������[i].֡[j - ֡ƫ��].�任.����.z = (m��������->Ƭ��[i].������[k].����[m].����[u + 1].����.x
                                            - m��������->Ƭ��[i].������[k].����[m].����[u].����.x) * l֡���� +
                                            m��������->Ƭ��[i].������[k].����[m].����[u].����.x;
                                        �����ڵ�->�������[i].֡[j - ֡ƫ��].�任.����.x = (m��������->Ƭ��[i].������[k].����[m].����[u + 1].����.y
                                            - m��������->Ƭ��[i].������[k].����[m].����[u].����.y) * l֡���� +
                                            m��������->Ƭ��[i].������[k].����[m].����[u].����.y;
                                        �����ڵ�->�������[i].֡[j - ֡ƫ��].�任.����.y = (m��������->Ƭ��[i].������[k].����[m].����[u + 1].����.z
                                            - m��������->Ƭ��[i].������[k].����[m].����[u].����.z) * l֡���� +
                                            m��������->Ƭ��[i].������[k].����[m].����[u].����.z;
                                    }
                            }

                            //��֡�����
                            if (m��������->Ƭ��[i].������[k].����[m].����.size() > 0)
                                if (m��������->Ƭ��[i].������[k].����[m].����[m��������->Ƭ��[i].������[k].����[m].����.size() - 1].֡�� <= j)
                                {
                                    �����ڵ�->�������[i].֡[j - ֡ƫ��].�任.����.z =
                                        m��������->Ƭ��[i].������[k].����[m].����[m��������->Ƭ��[i].������[k].����[m].����.size() - 1].����.x;
                                    �����ڵ�->�������[i].֡[j - ֡ƫ��].�任.����.x =
                                        m��������->Ƭ��[i].������[k].����[m].����[m��������->Ƭ��[i].������[k].����[m].����.size() - 1].����.y;
                                    �����ڵ�->�������[i].֡[j - ֡ƫ��].�任.����.y =
                                        m��������->Ƭ��[i].������[k].����[m].����[m��������->Ƭ��[i].������[k].����[m].����.size() - 1].����.z;
                                }
                        }
                    }
                }
            }
        }
    }

}

void C��̬����::�ϲ�������(S�任�ڵ�* �任�ڵ�)
{
    UINT i = 0;
    UINT j = 0;
    UINT k = 0;
    UINT m = 0;
    UINT n = 0;
    XMMATRIX ��ת�任{};
    XMMATRIX ��ת�任2{};
    XMMATRIX ��ת�任3{};
    XMMATRIX ��ת�任4{};
    XMMATRIX ��ת�任5{};
    XMMATRIX Ԥ��ת = XMMatrixIdentity();
    XMMATRIX Ԥ��ת2 = XMMatrixIdentity();
    XMMATRIX ��ת�任����{};
    XMMATRIX ��ʼ��ת{};
    XMMATRIX ��ʼ��ת2{};
    XMMATRIX ��һ��ת{};
    XMMATRIX ��һ��ת2{};
    XMMATRIX ��һ��ת��{};
    XMMATRIX ��һ��ʼ��ת{};
    XMMATRIX �������{};
    XMMATRIX ���ձ任{};
    XMMATRIX ����任 = XMMatrixIdentity();
    XMMATRIX ��ʼ��תƫ��{};
    XMVECTOR λ��{};
    XMVECTOR λ��2{};
    XMVECTOR λ��ƫ��{};
    XMMATRIX ��ת���� = XMMatrixIdentity();
    S�任�ڵ�* p�任�ڵ� = nullptr;
    S�任�ڵ�* p�任�ڵ�2 = nullptr;
    XMMATRIX ����ƫ�� = XMMatrixIdentity();
    bool �Ƿ�Ϊ����� = 0;
    int u = 0;
    int v = 0;

    for (j = 0; j < �������.size(); j++)
    {
        for (k = 0; k < �������[j].֡.size(); k++)
        {
            for (m = 0; m < �������[j].֡[k].�����任.size(); m++)
            {
                if (m��������[m] == �任�ڵ�->�ڵ�����)
                {
                    ���ձ任 = XMMatrixIdentity();
                    Ԥ��ת = XMMatrixIdentity();

                    p�任�ڵ� = �任�ڵ�;
                    while (p�任�ڵ�->���ڵ�)
                    {
                        �Ƿ�Ϊ����� = 1;
                        for (u = 0; u < 4; u++)
                            for (v = 0; v < 4; v++)
                                if (����->������[p�任�ڵ�->�ڵ�����].r[u].m128_f32[v] != 0.0f) �Ƿ�Ϊ����� = 0;
                        if (�Ƿ�Ϊ�����)
                        {
                            λ��2 = XMVECTOR{ -p�任�ڵ�->��ʼ����λ��.x, p�任�ڵ�->��ʼ����λ��.y, -p�任�ڵ�->��ʼ����λ��.z };
                            if (p�任�ڵ�->��ʼ����λ��.x == 0.0f && p�任�ڵ�->��ʼ����λ��.y == 0.0f && p�任�ڵ�->��ʼ����λ��.z == 0.0f)
                            {
                                λ��2.m128_f32[0] = p�任�ڵ�->ԭʼλ��.x;
                                λ��2.m128_f32[1] = p�任�ڵ�->ԭʼλ��.y;
                                λ��2.m128_f32[2] = p�任�ڵ�->ԭʼλ��.z;
                                λ��2 = XMVector3TransformCoord(λ��2, p�任�ڵ�->�������);
                                λ��2.m128_f32[0] = λ��2.m128_f32[0] + p�任�ڵ�->���ڵ�->�任.λ��.x;
                                λ��2.m128_f32[1] = λ��2.m128_f32[1] + p�任�ڵ�->���ڵ�->�任.λ��.y;
                                λ��2.m128_f32[2] = λ��2.m128_f32[2] + p�任�ڵ�->���ڵ�->�任.λ��.z;
                            }
                            ���ձ任 *= XMMatrixTranslation(-λ��2.m128_f32[0], -λ��2.m128_f32[1], -λ��2.m128_f32[2]);
                        }
                        else
                        {
                            λ�� = XMVECTOR{ ����->������[p�任�ڵ�->�ڵ�����].r[3].m128_f32[0], ����->������[p�任�ڵ�->�ڵ�����].r[3].m128_f32[1],
                                ����->������[p�任�ڵ�->�ڵ�����].r[3].m128_f32[2] };
                            ���ձ任 *= XMMatrixTranslation(-λ��.m128_f32[0], -λ��.m128_f32[1], -λ��.m128_f32[2]);
                        }

                        float rx = p�任�ڵ�->�������[j].֡[k].�任.��ת.x * XM_PI / 180;
                        float ry = p�任�ڵ�->�������[j].֡[k].�任.��ת.y * XM_PI / 180;
                        float rz = p�任�ڵ�->�������[j].֡[k].�任.��ת.z * XM_PI / 180;
                        ��ת�任4 = XMMatrixRotationRollPitchYaw(rx, ry, rz);
                        p�任�ڵ�2 = p�任�ڵ�;
                        while (p�任�ڵ�2->���ڵ�)
                        {
                            rx = p�任�ڵ�2->���ڵ�->�������[j].֡[k].�任.��ת.x * XM_PI / 180;
                            ry = p�任�ڵ�2->���ڵ�->�������[j].֡[k].�任.��ת.y * XM_PI / 180;
                            rz = p�任�ڵ�2->���ڵ�->�������[j].֡[k].�任.��ת.z * XM_PI / 180;
                            ��ת�任4 *= XMMatrixRotationRollPitchYaw(rx, ry, rz);

                            p�任�ڵ�2 = p�任�ڵ�2->���ڵ�;
                        }
                        ��ת�任2 = ����->������[p�任�ڵ�->�ڵ�����];
                        �Ƿ�Ϊ����� = 1;
                        for (u = 0; u < 4; u++)
                            for (v = 0; v < 4; v++)
                                if (��ת�任2.r[u].m128_f32[v] != 0.0f) �Ƿ�Ϊ����� = 0;
                        if (�Ƿ�Ϊ�����)
                        {
                            ��ת�任2 = XMLoadFloat3x3(&p�任�ڵ�->��ʼ������ת);
                            if (p�任�ڵ�->��ʼ������ת.m[0][0] == 1.0f && p�任�ڵ�->��ʼ������ת.m[1][1] == 1.0f &&
                                p�任�ڵ�->��ʼ������ת.m[2][2] == 1.0f)
                            {
                                rx = p�任�ڵ�->�������[j].֡[0].�任.��ת.x * XM_PI / 180;
                                ry = p�任�ڵ�->�������[j].֡[0].�任.��ת.y * XM_PI / 180;
                                rz = p�任�ڵ�->�������[j].֡[0].�任.��ת.z * XM_PI / 180;
                                ��ת�任2 = XMMatrixRotationRollPitchYaw(rx, ry, rz);
                                p�任�ڵ�2 = p�任�ڵ�;
                                while (p�任�ڵ�2->���ڵ�)
                                {
                                    rx = p�任�ڵ�2->���ڵ�->�������[j].֡[0].�任.��ת.x * XM_PI / 180;
                                    ry = p�任�ڵ�2->���ڵ�->�������[j].֡[0].�任.��ת.y * XM_PI / 180;
                                    rz = p�任�ڵ�2->���ڵ�->�������[j].֡[0].�任.��ת.z * XM_PI / 180;
                                    ��ת�任2 *= XMMatrixRotationRollPitchYaw(rx, ry, rz);

                                    p�任�ڵ�2 = p�任�ڵ�2->���ڵ�;
                                }
                            }
                        }
                        ��ת�任2.r[3].m128_f32[0] = 0.0f; ��ת�任2.r[3].m128_f32[1] = 0.0f; ��ת�任2.r[3].m128_f32[2] = 0.0f;
                        ��ת�任2 = XMMatrixInverse(0, ��ת�任2);

                        p�任�ڵ�2 = p�任�ڵ�;
                        rx = p�任�ڵ�2->���ڵ�->�������[j].֡[k].�任.��ת.x * XM_PI / 180;
                        ry = p�任�ڵ�2->���ڵ�->�������[j].֡[k].�任.��ת.y * XM_PI / 180;
                        rz = p�任�ڵ�2->���ڵ�->�������[j].֡[k].�任.��ת.z * XM_PI / 180;
                        ��ת�任 = XMMatrixRotationRollPitchYaw(rx, ry, rz);
                        p�任�ڵ�2 = p�任�ڵ�->���ڵ�;
                        while (p�任�ڵ�2->���ڵ�)
                        {
                            rx = p�任�ڵ�2->���ڵ�->�������[j].֡[k].�任.��ת.x * XM_PI / 180;
                            ry = p�任�ڵ�2->���ڵ�->�������[j].֡[k].�任.��ת.y * XM_PI / 180;
                            rz = p�任�ڵ�2->���ڵ�->�������[j].֡[k].�任.��ת.z * XM_PI / 180;
                            ��ת�任 *= XMMatrixRotationRollPitchYaw(rx, ry, rz);

                            p�任�ڵ�2 = p�任�ڵ�2->���ڵ�;
                        }
                        ��ת�任3 = ����->������[p�任�ڵ�->���ڵ�->�ڵ�����];
                        �Ƿ�Ϊ����� = 1;
                        for (u = 0; u < 4; u++)
                            for (v = 0; v < 4; v++)
                                if (��ת�任3.r[u].m128_f32[v] != 0.0f) �Ƿ�Ϊ����� = 0;
                        if (�Ƿ�Ϊ�����)
                        {
                            ��ת�任3 = XMLoadFloat3x3(&p�任�ڵ�->���ڵ�->��ʼ������ת);
                            if (p�任�ڵ�->���ڵ�->��ʼ������ת.m[0][0] == 1.0f && p�任�ڵ�->���ڵ�->��ʼ������ת.m[1][1] == 1.0f &&
                                p�任�ڵ�->���ڵ�->��ʼ������ת.m[2][2] == 1.0f)
                            {
                                rx = p�任�ڵ�->���ڵ�->�������[j].֡[0].�任.��ת.x * XM_PI / 180;
                                ry = p�任�ڵ�->���ڵ�->�������[j].֡[0].�任.��ת.y * XM_PI / 180;
                                rz = p�任�ڵ�->���ڵ�->�������[j].֡[0].�任.��ת.z * XM_PI / 180;
                                ��ת�任3 = XMMatrixRotationRollPitchYaw(rx, ry, rz);
                                p�任�ڵ�2 = p�任�ڵ�->���ڵ�;
                                while (p�任�ڵ�2->���ڵ�)
                                {
                                    rx = p�任�ڵ�2->���ڵ�->�������[j].֡[0].�任.��ת.x * XM_PI / 180;
                                    ry = p�任�ڵ�2->���ڵ�->�������[j].֡[0].�任.��ת.y * XM_PI / 180;
                                    rz = p�任�ڵ�2->���ڵ�->�������[j].֡[0].�任.��ת.z * XM_PI / 180;
                                    ��ת�任3 *= XMMatrixRotationRollPitchYaw(rx, ry, rz);

                                    p�任�ڵ�2 = p�任�ڵ�2->���ڵ�;
                                }
                            }
                        }
                        ��ת�任3.r[3].m128_f32[0] = 0.0f; ��ת�任3.r[3].m128_f32[1] = 0.0f; ��ת�任3.r[3].m128_f32[2] = 0.0f;

                        ��ת�任 = XMMatrixInverse(0, ��ת�任);

                        ���ձ任 = ���ձ任 * ��ת�任2 * ��ת�任4 * ��ת�任 * ��ת�任3;

                        ���ձ任 *= XMMatrixTranslation(λ��.m128_f32[0], λ��.m128_f32[1], λ��.m128_f32[2]);

                        Ԥ��ת *= �������[p�任�ڵ�->�ڵ�����].Ԥ��ת;
                        if (p�任�ڵ�->���ڵ�->�ڵ����� == L"���ڵ�")
                        {
                            Ԥ��ת2 = XMMatrixRotationAxis(XMVECTOR{ 0.0f, 0.0f, 1.0f, 0.0f }, XM_PI / 2);
                            ���ձ任 *= Ԥ��ת * Ԥ��ת2;
                        }

                        p�任�ڵ� = p�任�ڵ�->���ڵ�;
                    }

                    //p�任�ڵ� = �任�ڵ�;

                    //while (p�任�ڵ�->���ڵ�)
                    //{
                    //    if (p�任�ڵ�->���ڵ�->�ڵ����� == L"���ڵ�") break;
                    //    p�任�ڵ� = p�任�ڵ�->���ڵ�;
                    //}

                    //���ձ任 *= XMMatrixTranslation(p�任�ڵ�->�������[j].֡[k].�任.λ��.x - ����->������[p�任�ڵ�->�ڵ�����].r[3].m128_f32[0],
                    //    p�任�ڵ�->�������[j].֡[k].�任.λ��.y - ����->������[p�任�ڵ�->�ڵ�����].r[3].m128_f32[1],
                    //    p�任�ڵ�->�������[j].֡[k].�任.λ��.z - ����->������[p�任�ڵ�->�ڵ�����].r[3].m128_f32[2]);

                    XMStoreFloat4x3(&�������[j].֡[k].�����任[m], ���ձ任);

                }
            }
        }
    }

    for (i = 0; i < �任�ڵ�->�ӽڵ�����; i++)
    {
        �ϲ�������(&�任�ڵ�->�ӽڵ�[i]);
    }
}

void C��̬����::����ʱ��(float ʱ��仯)
{
    for (UINT i = 0; i < �������.size(); i++)
    {
        �������[i].��ǰʱ�� += ʱ��仯 * �������[i].�ٶ�;
        �������[i].�Ƿ���� = 1;
        if (�������[i].��ǰʱ�� >= �������[i].ԭʼʱ��)
        {
            if (�������[i].�Ƿ�ѭ��)
                �������[i].��ǰʱ�� = 0;
            else
                �������[i].��ǰʱ�� = �������[i].ԭʼʱ�� - 0.001;
        }

        �������[i].֡λ = �������[i].��ǰʱ�� / �������[i].ԭʼʱ�� * (�������[i].֡.size() - 1);
    }
}

XMMATRIX C��̬����::��ȡ��ǰ����任(UINT ����)
{
    UINT ֡�� = 0;
    float С�� = 0;
    XMMATRIX {};
    XMVECTOR ��תx{};
    XMVECTOR ��תy{};
    XMVECTOR ��תz{};
    XMVECTOR ��תx2{};
    XMVECTOR ��תy2{};
    XMVECTOR ��תz2{};
    XMVECTOR λ��{};
    XMVECTOR λ��2{};

    ֡�� = (int)�������[��ǰ���].֡λ;
    С�� = �������[��ǰ���].֡λ - ֡��;

    s����任 = XMLoadFloat4x3(&�������[��ǰ���].֡[֡��].����任[����]);

    λ�� = XMVECTOR{ �������[��ǰ���].֡[֡��].����任[����].m[3][0], �������[��ǰ���].֡[֡��].����任[����].m[3][1],
        �������[��ǰ���].֡[֡��].����任[����].m[3][2] };
    λ��2 = XMVECTOR{ �������[��ǰ���].֡[֡�� + 1].����任[����].m[3][0], �������[��ǰ���].֡[֡�� + 1].����任[����].m[3][1],
        �������[��ǰ���].֡[֡�� + 1].����任[����].m[3][2] };
    ��תx = XMVECTOR{ �������[��ǰ���].֡[֡��].����任[����].m[0][0], �������[��ǰ���].֡[֡��].����任[����].m[0][1],
        �������[��ǰ���].֡[֡��].����任[����].m[0][2], 0.0f };
    ��תy = XMVECTOR{ �������[��ǰ���].֡[֡��].����任[����].m[1][0], �������[��ǰ���].֡[֡��].����任[����].m[1][1],
        �������[��ǰ���].֡[֡��].����任[����].m[1][2], 0.0f };
    ��תz = XMVECTOR{ �������[��ǰ���].֡[֡��].����任[����].m[2][0], �������[��ǰ���].֡[֡��].����任[����].m[2][1],
        �������[��ǰ���].֡[֡��].����任[����].m[2][2], 0.0f };
    ��תx2 = XMVECTOR{ �������[��ǰ���].֡[֡�� + 1].����任[����].m[0][0], �������[��ǰ���].֡[֡�� + 1].����任[����].m[0][1],
        �������[��ǰ���].֡[֡�� + 1].����任[����].m[0][2], 0.0f };
    ��תy2 = XMVECTOR{ �������[��ǰ���].֡[֡�� + 1].����任[����].m[1][0], �������[��ǰ���].֡[֡�� + 1].����任[����].m[1][1],
        �������[��ǰ���].֡[֡�� + 1].����任[����].m[1][2], 0.0f };
    ��תz2 = XMVECTOR{ �������[��ǰ���].֡[֡�� + 1].����任[����].m[2][0], �������[��ǰ���].֡[֡�� + 1].����任[����].m[2][1],
        �������[��ǰ���].֡[֡�� + 1].����任[����].m[2][2], 0.0f };

    λ�� = λ�� * (1 - С��) + λ��2 * С��;
    ��תx = ��תx * (1 - С��) + ��תx2 * С��;
    ��תy = ��תy * (1 - С��) + ��תy2 * С��;
    ��תz = ��תz * (1 - С��) + ��תz2 * С��;

    s����任.r[0].m128_f32[0] = ��תx.m128_f32[0]; s����任.r[0].m128_f32[1] = ��תx.m128_f32[1]; s����任.r[0].m128_f32[2] = ��תx.m128_f32[2];
    s����任.r[1].m128_f32[0] = ��תy.m128_f32[0]; s����任.r[1].m128_f32[1] = ��תy.m128_f32[1]; s����任.r[1].m128_f32[2] = ��תy.m128_f32[2];
    s����任.r[2].m128_f32[0] = ��תz.m128_f32[0]; s����任.r[2].m128_f32[1] = ��תz.m128_f32[1]; s����任.r[2].m128_f32[2] = ��תz.m128_f32[2];
    s����任.r[3].m128_f32[0] = λ��.m128_f32[0]; s����任.r[3].m128_f32[1] = λ��.m128_f32[1]; s����任.r[3].m128_f32[2] = λ��.m128_f32[2];

    return s����任;
}

XMMATRIX* C��̬����::��ȡ��ǰ�����任()
{
    UINT l֡�� = 0;
    float lС�� = 0;
    XMVECTOR l����{};
    XMMATRIX l��ʼ��ת{};
    XMVECTOR ����λ��{};
    XMMATRIX l���ձ任{};
    XMMATRIX l����任{};
    XMVECTOR ��תx{};
    XMVECTOR ��תy{};
    XMVECTOR ��תz{};
    XMVECTOR ��תx2{};
    XMVECTOR ��תy2{};
    XMVECTOR ��תz2{};
    XMVECTOR λ��{};
    XMVECTOR λ��2{};
    XMMATRIX ��ת = XMMatrixIdentity();

    l֡�� = (int)�������[��ǰ���].֡λ;
    lС�� = �������[��ǰ���].֡λ - l֡��;

    for (UINT i = 1; i < ��������; i++)
    {
        l���ձ任 = XMLoadFloat4x3(&�������[��ǰ���].֡[l֡��].�����任[i]);
        λ�� = XMVECTOR{ �������[��ǰ���].֡[l֡��].�����任[i].m[3][0], �������[��ǰ���].֡[l֡��].�����任[i].m[3][1],
            �������[��ǰ���].֡[l֡��].�����任[i].m[3][2] };
        λ��2 = XMVECTOR{ �������[��ǰ���].֡[l֡�� + 1].�����任[i].m[3][0], �������[��ǰ���].֡[l֡�� + 1].�����任[i].m[3][1],
            �������[��ǰ���].֡[l֡�� + 1].�����任[i].m[3][2] };
        ��תx = XMVECTOR{ �������[��ǰ���].֡[l֡��].�����任[i].m[0][0], �������[��ǰ���].֡[l֡��].�����任[i].m[0][1],
            �������[��ǰ���].֡[l֡��].�����任[i].m[0][2], 0.0f };
        ��תy = XMVECTOR{ �������[��ǰ���].֡[l֡��].�����任[i].m[1][0], �������[��ǰ���].֡[l֡��].�����任[i].m[1][1],
            �������[��ǰ���].֡[l֡��].�����任[i].m[1][2], 0.0f };
        ��תz = XMVECTOR{ �������[��ǰ���].֡[l֡��].�����任[i].m[2][0], �������[��ǰ���].֡[l֡��].�����任[i].m[2][1],
            �������[��ǰ���].֡[l֡��].�����任[i].m[2][2], 0.0f };
        ��תx2 = XMVECTOR{ �������[��ǰ���].֡[l֡�� + 1].�����任[i].m[0][0], �������[��ǰ���].֡[l֡�� + 1].�����任[i].m[0][1],
            �������[��ǰ���].֡[l֡�� + 1].�����任[i].m[0][2], 0.0f };
        ��תy2 = XMVECTOR{ �������[��ǰ���].֡[l֡�� + 1].�����任[i].m[1][0], �������[��ǰ���].֡[l֡�� + 1].�����任[i].m[1][1],
            �������[��ǰ���].֡[l֡�� + 1].�����任[i].m[1][2], 0.0f };
        ��תz2 = XMVECTOR{ �������[��ǰ���].֡[l֡�� + 1].�����任[i].m[2][0], �������[��ǰ���].֡[l֡�� + 1].�����任[i].m[2][1],
            �������[��ǰ���].֡[l֡�� + 1].�����任[i].m[2][2], 0.0f };
        λ�� = λ�� * (1 - lС��) + λ��2 * lС��;
        ��תx = ��תx * (1 - lС��) + ��תx2 * lС��;
        ��תy = ��תy * (1 - lС��) + ��תy2 * lС��;
        ��תz = ��תz * (1 - lС��) + ��תz2 * lС��;
        l���ձ任.r[0].m128_f32[0] = ��תx.m128_f32[0]; l���ձ任.r[0].m128_f32[1] = ��תx.m128_f32[1]; l���ձ任.r[0].m128_f32[2] = ��תx.m128_f32[2];
        l���ձ任.r[1].m128_f32[0] = ��תy.m128_f32[0]; l���ձ任.r[1].m128_f32[1] = ��תy.m128_f32[1]; l���ձ任.r[1].m128_f32[2] = ��תy.m128_f32[2];
        l���ձ任.r[2].m128_f32[0] = ��תz.m128_f32[0]; l���ձ任.r[2].m128_f32[1] = ��תz.m128_f32[1]; l���ձ任.r[2].m128_f32[2] = ��תz.m128_f32[2];
        l���ձ任.r[3].m128_f32[0] = λ��.m128_f32[0]; l���ձ任.r[3].m128_f32[1] = λ��.m128_f32[1]; l���ձ任.r[3].m128_f32[2] = λ��.m128_f32[2];

        s�����任[i] = l���ձ任;
    }

    return s�����任;
}

void C��̬����::�趨�����ٶ�(UINT ���, float �ٶȱ���)
{
    �������[���].�ٶ� = �ٶȱ���;
}

void C��̬����::�趨�������(UINT ���)
{
    ��ǰ��� = ���;
}

void C��̬����::�趨���֡λ��(UINT ���, float �ٷֱ�)
{
    �������[���].��ǰʱ�� = �������[���].ԭʼʱ�� * �ٷֱ�;
}

void C��̬����::�趨����ģʽ(UINT ���, bool �Ƿ�ѭ��)
{
    �������[���].�Ƿ�ѭ�� = �Ƿ�ѭ��;
}

bool C��̬����::��⶯������(UINT ���)
{
    if (�������[���].�Ƿ����) return 1;
    else return 0;
}

void C��̬����::���������Ż���Ϣ(float �������ϲ����Ƕ�, float ��ͼ������������)
{
    this->�������ϲ����Ƕ� = �������ϲ����Ƕ�;
    this->��ͼ������������ = ��ͼ������������;
}

void C��̬����::�ͷźϲ�����������()
{
    m�ϲ�������.clear();
    m�ϲ�������.shrink_to_fit();
}

void C��̬����::�ͷ��ϴ���()
{
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
    delete m��Ƥ����; m��Ƥ���� = nullptr;
    delete m��������; m�������� = nullptr;
    //delete m���ڵ�; m���ڵ� = nullptr;
    delete ����; ���� = nullptr;
    m�Ż����㼯.clear();
    m�Ż����㼯.shrink_to_fit();
    �������.clear();
}

C��̬����::~C��̬����()
{
    delete ����; ���� = nullptr;
    delete[] s�����任; s�����任 = nullptr;
    delete s��������; s�������� = nullptr;
    if (���㼯) delete[] ���㼯; ���㼯 = nullptr;
    m��������.clear();
    m��������.shrink_to_fit();
    delete m���ڵ�; m���ڵ� = nullptr;
}
