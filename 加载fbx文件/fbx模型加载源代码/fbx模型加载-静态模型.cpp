#include"fbx模型加载-静态模型.h"
#include"网格属性.h"

C静态物体::C静态物体(ComPtr<ID3D12Device> 设备, ComPtr<ID3D12GraphicsCommandList> 命令队列, C描述符堆管理* 描述符堆管理, C共享资源* 共享资源)
{
    this->设备 = 设备;
    this->命令队列 = 命令队列;
    this->描述符堆管理 = 描述符堆管理;
    this->共享资源 = 共享资源;
}

//导出文件mds文件-----------------------------------
void C静态物体::导出mds文件(wstring 文件名称)
{
    ofstream 输出文件;
    string 文件内容;
    wstring 图片名称;
    WCHAR 文件基础路径[128]{};
    wstring 文件名称2;
    char 图片名称2[128]{};
    wstring 图片名称3;
    UINT 字符串长度 = 0;
    int i = 0;
    int j = 0;

    wcscpy_s(文件基础路径, 文件名称.c_str());
    for (int i = 0; i < wcslen(文件基础路径); i++)
    {
        if (文件基础路径[i] == '.')
        {
            文件基础路径[i] = '\0';
            break;
        }
    }

    if (CreateDirectory(文件基础路径, 0) == 0)
    {
        wstring bug = L"文件覆盖 line:" + to_wstring(__LINE__) + L'\n';
        OutputDebugString(bug.c_str());
    }

    文件名称2 = 文件基础路径;
    文件名称 = 文件名称2 + L"\\" + 文件名称;

    输出文件.open(文件名称);

    if (!输出文件.is_open())
    {
        wstring bug = L"文件无法打开 line:" + to_wstring(__LINE__) + L'\n';
        OutputDebugString(bug.c_str());
        PostQuitMessage(0);
        return;
    }

    文件内容 = "属性数量：" + to_string(属性->元素.size()) + "；\n";
    输出文件.write(文件内容.c_str(), 文件内容.size());

    for (i = 0; i < s备用资料->路径集.size(); i++)
    {
        图片名称.clear();
        j = 0;
        while (1)
        {
            if (s备用资料->路径集[i][j] != '\0')
            {
                if (s备用资料->路径集[i][j] == '/' || s备用资料->路径集[i][j] == '\\')
                {
                    图片名称.clear();
                    j++;
                }
                图片名称 += s备用资料->路径集[i][j];
                j++;
            }
            else
            {
                break;
            }
        }

        WideCharToMultiByte(CP_ACP, 0, 图片名称.c_str(), 图片名称.size(), 图片名称2, 128, 0, 0);

        图片名称3 = 图片名称;
        图片名称 = 文件基础路径;
        图片名称 += L'\\';
        图片名称 += 图片名称3;

        CopyFile(s备用资料->路径集[i].c_str(), 图片名称.c_str(), TRUE);

        文件内容 = "材质名称：";
        文件内容 += 图片名称2;
        文件内容 += "；\n";
        输出文件.write(文件内容.c_str(), 文件内容.size());
    }

    文件内容 = "\n";
    输出文件.write(文件内容.c_str(), 文件内容.size());

    for (i = 0; i < 属性->元素.size(); i++)
    {
        char 缓存[128];
        int 长度 = WideCharToMultiByte(CP_ACP, 0, 属性->元素[i]->物体名称.c_str(), 属性->元素[i]->物体名称.size(), 缓存, 128, 0, 0);
        缓存[长度] = '\0';
        string 物体名称 = 缓存;

        文件内容 = "网格属性.物体名称：" + 物体名称 + "；\n"; to_string(1);
        输出文件.write(文件内容.c_str(), 文件内容.size());

        文件内容 = "网格属性.起始索引：" + to_string(属性->元素[i]->起始索引) + "；\n";
        输出文件.write(文件内容.c_str(), 文件内容.size());

        文件内容 = "网格属性.索引数量：" + to_string(属性->元素[i]->索引数量) + "；\n";
        输出文件.write(文件内容.c_str(), 文件内容.size());

        文件内容 = "网格属性.变换矩阵：" + to_string(属性->元素[i]->变换.r[0].m128_f32[0]) + "；" +
            to_string(属性->元素[i]->变换.r[0].m128_f32[1]) + "；" + to_string(属性->元素[i]->变换.r[0].m128_f32[2]) + "；" +
            to_string(属性->元素[i]->变换.r[0].m128_f32[3]) + "；" + to_string(属性->元素[i]->变换.r[1].m128_f32[0]) + "；" +
            to_string(属性->元素[i]->变换.r[1].m128_f32[1]) + "；" + to_string(属性->元素[i]->变换.r[1].m128_f32[2]) + "；" +
            to_string(属性->元素[i]->变换.r[1].m128_f32[3]) + "；" + to_string(属性->元素[i]->变换.r[2].m128_f32[0]) + "；" +
            to_string(属性->元素[i]->变换.r[2].m128_f32[1]) + "；" + to_string(属性->元素[i]->变换.r[2].m128_f32[2]) + "；" +
            to_string(属性->元素[i]->变换.r[2].m128_f32[3]) + "；" + to_string(属性->元素[i]->变换.r[3].m128_f32[0]) + "；" +
            to_string(属性->元素[i]->变换.r[3].m128_f32[1]) + "；" + to_string(属性->元素[i]->变换.r[3].m128_f32[2]) + "；" +
            to_string(属性->元素[i]->变换.r[3].m128_f32[3]) + "；\n";
        输出文件.write(文件内容.c_str(), 文件内容.size());

        文件内容 = "网格属性.纹理索引：" + to_string(属性->元素[i]->纹理索引) + "；\n";
        输出文件.write(文件内容.c_str(), 文件内容.size());

        文件内容 = "网格属性.法线图索引：" + to_string(属性->元素[i]->法线图索引) + "；\n";
        输出文件.write(文件内容.c_str(), 文件内容.size());

        文件内容 = "网格属性.材质.漫反射：" + to_string(属性->元素[i]->材质.漫反射.x) + "；" + 
            to_string(属性->元素[i]->材质.漫反射.y) + "；" + to_string(属性->元素[i]->材质.漫反射.z) + "；" + 
            to_string(属性->元素[i]->材质.漫反射.w) + "；\n";
        输出文件.write(文件内容.c_str(), 文件内容.size());

        文件内容 = "网格属性.材质.自发光：" + to_string(属性->元素[i]->材质.自发光.x) + "；" +
            to_string(属性->元素[i]->材质.自发光.y) + "；" + to_string(属性->元素[i]->材质.自发光.z) + "；" +
            to_string(属性->元素[i]->材质.自发光.w) + "；\n";
        输出文件.write(文件内容.c_str(), 文件内容.size());

        文件内容 = "网格属性.材质.环境光：" + to_string(属性->元素[i]->材质.环境光.x) + "；" +
            to_string(属性->元素[i]->材质.环境光.y) + "；" + to_string(属性->元素[i]->材质.环境光.z) + "；" +
            to_string(属性->元素[i]->材质.环境光.w) + "；\n";
        输出文件.write(文件内容.c_str(), 文件内容.size());

        文件内容 = "网格属性.材质.光泽度：" + to_string(属性->元素[i]->材质.光泽度) + "；\n";
        输出文件.write(文件内容.c_str(), 文件内容.size());

        文件内容 = "网格属性.材质.高光级别：" + to_string(属性->元素[i]->材质.高光级别) + "；\n";
        输出文件.write(文件内容.c_str(), 文件内容.size());

        文件内容 = "网格属性.材质.不透明度：" + to_string(属性->元素[i]->材质.不透明度) + "；\n";
        输出文件.write(文件内容.c_str(), 文件内容.size());

        文件内容 = "网格属性.包围球.中心：" + to_string(属性->元素[i]->包围球.Center.x) + "；" + to_string(属性->元素[i]->包围球.Center.y) + "；"
            + to_string(属性->元素[i]->包围球.Center.z) + "；\n";
        输出文件.write(文件内容.c_str(), 文件内容.size());

        文件内容 = "网格属性.包围球.半径：" + to_string(属性->元素[i]->包围球.Radius) + "；\n";
        输出文件.write(文件内容.c_str(), 文件内容.size());

        文件内容 = "网格属性.包围框块.包围框数量：" + to_string(s备用资料->包围框块[i].size()) + "；\n";
        输出文件.write(文件内容.c_str(), 文件内容.size());

        for (int j = 0; j < s备用资料->包围框块[i].size(); j++)
        {
            文件内容 = "包围框块.左下前位置：" + to_string(s备用资料->包围框块[i][j].左下前位置.x) + "；" + to_string(s备用资料->包围框块[i][j].左下前位置.y)
                + "；" + to_string(s备用资料->包围框块[i][j].左下前位置.z) + "；\n";
            输出文件.write(文件内容.c_str(), 文件内容.size());

            文件内容 = "包围框块.边长：" + to_string(s备用资料->包围框块[i][j].边长.x) + "；" + to_string(s备用资料->包围框块[i][j].边长.y)
                + "；" + to_string(s备用资料->包围框块[i][j].边长.z) + "；\n";
            输出文件.write(文件内容.c_str(), 文件内容.size());

            文件内容 = "\n";
            输出文件.write(文件内容.c_str(), 文件内容.size());
        }

        文件内容 = "\n";
        输出文件.write(文件内容.c_str(), 文件内容.size());
    }

    文件内容 = "\n";
    输出文件.write(文件内容.c_str(), 文件内容.size());

    文件内容 = "顶点布局：" + to_string(顶点布局) + "；\n";
    输出文件.write(文件内容.c_str(), 文件内容.size());

    文件内容 = "顶点单元大小：" + to_string(顶点单元大小) + "；\n";
    输出文件.write(文件内容.c_str(), 文件内容.size());

    文件内容 = "顶点数量：" + to_string(s备用资料->顶点集.size()) + "；\n";
    输出文件.write(文件内容.c_str(), 文件内容.size());

    文件内容 = "\n";
    输出文件.write(文件内容.c_str(), 文件内容.size());
    for (i = 0; i < s备用资料->顶点集.size(); i++)
    {
        s备用资料->顶点集[i].位置;

        文件内容 = "顶点.位置：" + to_string(s备用资料->顶点集[i].位置.x) + "；" +
            to_string(s备用资料->顶点集[i].位置.y) + "；" + to_string(s备用资料->顶点集[i].位置.z) + "；\n";
        输出文件.write(文件内容.c_str(), 文件内容.size());

        文件内容 = "顶点.法向量：" + to_string(s备用资料->顶点集[i].法向量.x) + "；" + 
            to_string(s备用资料->顶点集[i].法向量.y) + "；" + to_string(s备用资料->顶点集[i].法向量.z) + "；\n";
        输出文件.write(文件内容.c_str(), 文件内容.size());

        文件内容 = "顶点.纹理：" + to_string(s备用资料->顶点集[i].纹理坐标.x) + "；" +
            to_string(s备用资料->顶点集[i].纹理坐标.y) + "；\n";
        输出文件.write(文件内容.c_str(), 文件内容.size());

        文件内容 = "\n";
        输出文件.write(文件内容.c_str(), 文件内容.size());
    }

    文件内容 = "\n";
    输出文件.write(文件内容.c_str(), 文件内容.size());

    文件内容 = "索引格式：" + to_string(索引格式) + "；\n";
    输出文件.write(文件内容.c_str(), 文件内容.size());

    文件内容 = "索引数量：" + to_string(索引数量) + "；\n";
    输出文件.write(文件内容.c_str(), 文件内容.size());

    if (索引格式 == DXGI_FORMAT_R16_UINT)
    {
        for (i = 0; i < s备用资料->s索引.size(); i = i + 3)
        {
            文件内容 = "三角形索引：" + to_string(s备用资料->s索引[i]) + "；" + to_string(s备用资料->s索引[i + 1]) + "；" +
                to_string(s备用资料->s索引[i + 2]) + "；\n";
            输出文件.write(文件内容.c_str(), 文件内容.size());
        }
    }
    else if (索引格式 == DXGI_FORMAT_R32_UINT)
    {
        for (i = 0; i < s备用资料->索引.size(); i = i + 3)
        {
            文件内容 = "三角形索引：" + to_string(s备用资料->索引[i]) + "；" + to_string(s备用资料->索引[i + 1]) + "；" +
                to_string(s备用资料->索引[i + 2]) + "；\n";
            输出文件.write(文件内容.c_str(), 文件内容.size());
        }
    }

    文件内容 = "\n";
    输出文件.write(文件内容.c_str(), 文件内容.size());

    输出文件.close();
}

//导入文件
void C静态物体::导入mds文件(wstring 文件名称, wstring 物体名称键)
{
    ifstream 输入文件;
    wstring 关键字 = L"";
    wstring 数值[20];
    char 数值2[128]{};
    char 内容[256];
    WCHAR 内容2[256];
    int 步骤 = 0;
    int i = 0;
    UINT 属性步骤 = 0;
    map<wstring, int> id;
    UINT 顶点索引 = 0;
    UINT 顶点步骤 = 0;
    UINT 索引步骤 = 0;
    UINT 字符串长度 = 0;
    string 基础路径 = "";
    char 图片名称[128]{};
    WCHAR 图片名称w[128]{};
    WCHAR 基础路径w[128]{};
    int 长度 = 0;
    UINT 包围框步骤 = 0;
    wstring 文件类型;
    bool 是否启录 = 0;

    this->物体名称键 = 物体名称键;

    id.insert(pair<wstring, int>(L"属性数量", 0));
    id.insert(pair<wstring, int>(L"网格属性.物体名称", 1));
    id.insert(pair<wstring, int>(L"网格属性.起始索引", 2));
    id.insert(pair<wstring, int>(L"网格属性.索引数量", 3));
    id.insert(pair<wstring, int>(L"网格属性.变换矩阵", 4));
    id.insert(pair<wstring, int>(L"网格属性.纹理索引", 5));
    id.insert(pair<wstring, int>(L"网格属性.法线图索引", 6));
    id.insert(pair<wstring, int>(L"网格属性.材质.漫反射", 7));
    id.insert(pair<wstring, int>(L"网格属性.材质.自发光", 8));
    id.insert(pair<wstring, int>(L"网格属性.材质.环境光", 9));
    id.insert(pair<wstring, int>(L"网格属性.材质.光泽度", 10));
    id.insert(pair<wstring, int>(L"网格属性.材质.高光级别", 11));
    id.insert(pair<wstring, int>(L"网格属性.材质.不透明度", 12));
    id.insert(pair<wstring, int>(L"顶点布局", 13));
    id.insert(pair<wstring, int>(L"顶点单元大小", 14));
    id.insert(pair<wstring, int>(L"顶点数量", 15));
    id.insert(pair<wstring, int>(L"顶点.位置", 16));
    id.insert(pair<wstring, int>(L"顶点.法向量", 17));
    id.insert(pair<wstring, int>(L"顶点.纹理", 18));
    id.insert(pair<wstring, int>(L"索引格式", 19));
    id.insert(pair<wstring, int>(L"索引数量", 20));
    id.insert(pair<wstring, int>(L"三角形索引", 21));
    id.insert(pair<wstring, int>(L"材质名称", 22));
    id.insert(pair<wstring, int>(L"网格属性.包围球.中心", 23));
    id.insert(pair<wstring, int>(L"网格属性.包围球.半径", 24));
    id.insert(pair<wstring, int>(L"网格属性.包围框块.包围框数量", 25));
    id.insert(pair<wstring, int>(L"包围框块.左下前位置", 26));
    id.insert(pair<wstring, int>(L"包围框块.边长", 27));

    输入文件.open(文件名称);

    if (!输入文件.is_open())
    {
        wstring bug = L"文件无法打开 line:" + to_wstring(__LINE__) + L'\n';
        OutputDebugString(bug.c_str());
        PostQuitMessage(0);
        return;
    }

    s备用资料 = new S备用资料;

    while (!输入文件.eof())
    {
        关键字.clear();
        for(i = 0; i < 步骤; i++)
            数值[i].clear();
        步骤 = 0;

        输入文件.getline(内容, 256);
        字符串长度 = MultiByteToWideChar(CP_ACP, 0, 内容, strlen(内容), 内容2, 256);
        内容2[字符串长度] = '\0';

        i = 0;
        while (1)
        {
            if (内容2[i] == L'：')
            {
                i++;
                步骤 = 1;
            }

            if (内容2[i] == L'；')
            {
                i++;
                步骤++;
            }

            if (内容2[i] == L'\0') break;
            
            if (步骤 == 0)
                关键字 += 内容2[i];

            if (步骤 > 0)
                数值[步骤 - 1] += 内容2[i];

            i++;
        }

        if(关键字[0] != L'\0')
            switch (id[关键字])
            {
            case 0:
                属性 = new C网格属性;
                属性->元素.resize(stoi(数值[0]));
                for (int i = 0; i < 属性->元素.size(); i++)
                {
                    属性->元素[i] = new C网格属性::S属性;
                }
                s备用资料->包围框块.resize(stoi(数值[0]));
                属性->纹理集.resize(1);
                属性->纹理集[0] = 共享资源->白贴图;
                属性->纹理集上传.resize(1);
                属性->纹理集上传[0] = nullptr;
                break;

            case 1:
                属性->元素[属性步骤]->物体名称 = 数值[0];
                break;

            case 2:
                属性->元素[属性步骤]->起始索引 = stoi(数值[0]);
                break;

            case 3:
                属性->元素[属性步骤]->索引数量 = stoi(数值[0]);
                break;

            case 4:
                属性->元素[属性步骤]->变换.r[0].m128_f32[0] = stof(数值[0]); 属性->元素[属性步骤]->变换.r[0].m128_f32[1] = stof(数值[1]);
                属性->元素[属性步骤]->变换.r[0].m128_f32[2] = stof(数值[2]); 属性->元素[属性步骤]->变换.r[0].m128_f32[3] = stof(数值[3]);
                属性->元素[属性步骤]->变换.r[1].m128_f32[0] = stof(数值[4]); 属性->元素[属性步骤]->变换.r[1].m128_f32[1] = stof(数值[5]);
                属性->元素[属性步骤]->变换.r[1].m128_f32[2] = stof(数值[6]); 属性->元素[属性步骤]->变换.r[1].m128_f32[3] = stof(数值[7]);
                属性->元素[属性步骤]->变换.r[2].m128_f32[0] = stof(数值[8]); 属性->元素[属性步骤]->变换.r[2].m128_f32[1] = stof(数值[9]);
                属性->元素[属性步骤]->变换.r[2].m128_f32[2] = stof(数值[10]); 属性->元素[属性步骤]->变换.r[2].m128_f32[3] = stof(数值[11]);
                属性->元素[属性步骤]->变换.r[3].m128_f32[0] = stof(数值[12]); 属性->元素[属性步骤]->变换.r[3].m128_f32[1] = stof(数值[13]);
                属性->元素[属性步骤]->变换.r[3].m128_f32[2] = stof(数值[14]); 属性->元素[属性步骤]->变换.r[3].m128_f32[3] = stof(数值[15]);
                break;

            case 5:
                属性->元素[属性步骤]->纹理索引 = stoi(数值[0]);
                break;

            case 6:
                属性->元素[属性步骤]->法线图索引 = stoi(数值[0]);
                break;

            case 7:
                属性->元素[属性步骤]->材质.漫反射.x = stof(数值[0]); 属性->元素[属性步骤]->材质.漫反射.y = stof(数值[1]);
                属性->元素[属性步骤]->材质.漫反射.z = stof(数值[2]); 属性->元素[属性步骤]->材质.漫反射.w = stof(数值[3]);
                break;

            case 8:
                属性->元素[属性步骤]->材质.自发光.x = stof(数值[0]); 属性->元素[属性步骤]->材质.自发光.y = stof(数值[1]);
                属性->元素[属性步骤]->材质.自发光.z = stof(数值[2]); 属性->元素[属性步骤]->材质.自发光.w = stof(数值[3]);
                break;

            case 9:
                属性->元素[属性步骤]->材质.环境光.x = stof(数值[0]); 属性->元素[属性步骤]->材质.环境光.y = stof(数值[1]);
                属性->元素[属性步骤]->材质.环境光.z = stof(数值[2]); 属性->元素[属性步骤]->材质.环境光.w = stof(数值[3]);
                break;

            case 10:
                属性->元素[属性步骤]->材质.光泽度 = stoi(数值[0]);
                break;

            case 11:
                属性->元素[属性步骤]->材质.高光级别 = stoi(数值[0]);
                break;

            case 12:
                属性->元素[属性步骤]->材质.不透明度 = stoi(数值[0]);
                break;

            case 15:
                顶点数量 = stoi(数值[0]);
                s备用资料->顶点集.resize(顶点数量);
                break;

            case 16:
                s备用资料->顶点集[顶点步骤].位置.x = stof(数值[0]); s备用资料->顶点集[顶点步骤].位置.y = stof(数值[1]); 
                s备用资料->顶点集[顶点步骤].位置.z = stof(数值[2]);
                break;

            case 17:
                s备用资料->顶点集[顶点步骤].法向量.x = stof(数值[0]); s备用资料->顶点集[顶点步骤].法向量.y = stof(数值[1]); 
                s备用资料->顶点集[顶点步骤].法向量.z = stof(数值[2]);
                break;

            case 18:
                s备用资料->顶点集[顶点步骤].纹理坐标.x = stof(数值[0]); s备用资料->顶点集[顶点步骤].纹理坐标.y = stof(数值[1]);
                顶点步骤++;
                break;

            case 19:
                索引格式 = (DXGI_FORMAT)stoi(数值[0]);
                break;

            case 20:
                索引数量 = stoi(数值[0]);
                if (索引格式 == DXGI_FORMAT_R32_UINT)
                    s备用资料->索引.resize(索引数量);

                if (索引格式 == DXGI_FORMAT_R16_UINT)
                    s备用资料->s索引.resize(索引数量);

                break;

            case 21:
                if (索引格式 == DXGI_FORMAT_R32_UINT)
                {
                    s备用资料->索引[索引步骤] = stoi(数值[0]); s备用资料->索引[索引步骤 + 1] = stoi(数值[1]); 
                    s备用资料->索引[索引步骤 + 2] = stoi(数值[2]);
                    索引步骤 += 3;
                }
                if (索引格式 == DXGI_FORMAT_R16_UINT)
                {
                    s备用资料->s索引[索引步骤] = stoi(数值[0]); s备用资料->s索引[索引步骤 + 1] = stoi(数值[1]); 
                    s备用资料->s索引[索引步骤 + 2] = stoi(数值[2]);
                    索引步骤 += 3;
                }
                break;

            case 22:
                i = 0;
                while (文件名称[i] != '\0')
                {
                    图片名称w[i] = 文件名称[i];
                    i++;
                }
                长度 = WideCharToMultiByte(CP_ACP, 0, 图片名称w, wcslen(图片名称w), 图片名称, 128, 0, 0);
                图片名称[长度] = '\0';
                
                i = strlen(图片名称);
                while (1)
                {
                    i--;
                    if (图片名称[i] == '/')
                    {
                        图片名称[i] = '\0';
                        break;
                    }
                    else if (图片名称[i] == '\\')
                    {
                        图片名称[i] = '\0';
                        break;
                    }
                }

                基础路径 = 图片名称;

                字符串长度 = WideCharToMultiByte(CP_ACP, 0, 数值[0].c_str(), wcslen(数值[0].c_str()), 图片名称, 128, 0, 0);
                图片名称[字符串长度] = 0;

                基础路径 += "//"; 
                基础路径 += 图片名称;

                for (i = 0; i < s备用资料->路径集.size(); i++)
                {
                    char 路径[128]{};
                    int 长度 = WideCharToMultiByte(CP_ACP, 0, s备用资料->路径集[i].c_str(), s备用资料->路径集[i].size(), 路径, 128, 0, 0);
                    路径[长度] = 0;

                    if (基础路径 == 路径)
                    {
                        goto 跳出;
                    }
                }

                长度 = MultiByteToWideChar(CP_ACP, 0, 基础路径.c_str(), 基础路径.size(), 基础路径w, 128);
                基础路径w[长度] = 0;

                s备用资料->路径集.push_back(基础路径w);

                文件类型.clear();
                是否启录 = 0;
                for (int i = 0; i < wcslen(基础路径w); i++)
                {
                    if (是否启录) 文件类型 += 基础路径w[i];
                    if (基础路径w[i] == '.')
                    {
                        是否启录 = 1;
                        文件类型.clear();
                    }
                }

                属性->纹理集.resize(属性->纹理集.size() + 1);
                属性->纹理集上传.resize(属性->纹理集上传.size() + 1);
                if (文件类型 == L"dds")
                {
                    if (!SUCCEEDED(CreateDDSTextureFromFile12(设备.Get(), 命令队列.Get(), 基础路径w,
                        this->属性->纹理集[this->属性->纹理集.size() - 1], this->属性->纹理集上传[this->属性->纹理集上传.size() - 1])))
                    {
                        wstring bug = L"加载mds文件时找不到贴图 line:" + to_wstring(__LINE__) + L'\n';
                        OutputDebugString(bug.c_str());
                        PostQuitMessage(0);
                    }
                }
                else
                {
                    if (!SUCCEEDED(CreateImageDataTextureFromFile(设备.Get(), 命令队列.Get(), 基础路径w,
                        this->属性->纹理集[this->属性->纹理集.size() - 1], this->属性->纹理集上传[this->属性->纹理集上传.size() - 1])))
                    {
                        wstring bug = L"加载模型材质时未找到贴图文件 line:";
                        bug += to_wstring(__LINE__) + L"\n";
                        OutputDebugString(bug.c_str());
                        PostQuitMessage(0);
                    }
                }

                跳出:
                break;

            case 23:
                属性->元素[属性步骤]->包围球.Center.x = stof(数值[0]); 属性->元素[属性步骤]->包围球.Center.y = stof(数值[1]);
                属性->元素[属性步骤]->包围球.Center.z = stof(数值[2]);
                break;

            case 24:
                属性->元素[属性步骤]->包围球.Radius = stof(数值[0]);
                break;

            case 25:
                s备用资料->包围框块[属性步骤].resize(stoi(数值[0]));
                包围框步骤 = 0;
                属性步骤++;
                break;

            case 26:
                s备用资料->包围框块[属性步骤 - 1][包围框步骤].左下前位置.x = stof(数值[0]);
                s备用资料->包围框块[属性步骤 - 1][包围框步骤].左下前位置.y = stof(数值[1]);
                s备用资料->包围框块[属性步骤 - 1][包围框步骤].左下前位置.z = stof(数值[2]);
                break;

            case 27:
                s备用资料->包围框块[属性步骤 - 1][包围框步骤].边长.x = stof(数值[0]);
                s备用资料->包围框块[属性步骤 - 1][包围框步骤].边长.y = stof(数值[1]);
                s备用资料->包围框块[属性步骤 - 1][包围框步骤].边长.z = stof(数值[2]);
                包围框步骤++;
                break;

            default:
                break;
            }

    }

    输入文件.close();

    顶点布局 = FVF位置 | FVF法向量 | FVF纹理坐标;
    顶点单元大小 = sizeof(S顶点);

    D3D12_HEAP_PROPERTIES HeapProperties = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT);
    D3D12_RESOURCE_DESC Desc = CD3DX12_RESOURCE_DESC::Buffer(sizeof(S顶点) * s备用资料->顶点集.size());
    设备->CreateCommittedResource(
        &HeapProperties,
        D3D12_HEAP_FLAG_NONE,
        &Desc,
        D3D12_RESOURCE_STATE_COMMON,
        nullptr,
        IID_PPV_ARGS(&顶点));

    HeapProperties = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
    Desc = CD3DX12_RESOURCE_DESC::Buffer(sizeof(S顶点) * s备用资料->顶点集.size());
    设备->CreateCommittedResource(
        &HeapProperties,
        D3D12_HEAP_FLAG_NONE,
        &Desc,
        D3D12_RESOURCE_STATE_GENERIC_READ,
        nullptr,
        IID_PPV_ARGS(&顶点上传));

    D3D12_SUBRESOURCE_DATA subResourceData = {};
    subResourceData.pData = s备用资料->顶点集.data();
    subResourceData.RowPitch = sizeof(S顶点) * s备用资料->顶点集.size();
    subResourceData.SlicePitch = subResourceData.RowPitch;

    D3D12_RESOURCE_BARRIER pBarriers = CD3DX12_RESOURCE_BARRIER::Transition(顶点.Get(),
        D3D12_RESOURCE_STATE_COMMON, D3D12_RESOURCE_STATE_COPY_DEST);
    命令队列->ResourceBarrier(1, &pBarriers);
    UpdateSubresources<1>(命令队列.Get(), 顶点.Get(), 顶点上传.Get(), 0, 0, 1, &subResourceData);
    pBarriers = CD3DX12_RESOURCE_BARRIER::Transition(顶点.Get(),
        D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_GENERIC_READ);
    命令队列->ResourceBarrier(1, &pBarriers);

    vbv.BufferLocation = 顶点->GetGPUVirtualAddress();
    vbv.StrideInBytes = sizeof(S顶点);
    vbv.SizeInBytes = sizeof(S顶点) * s备用资料->顶点集.size();

    switch (索引格式)
    {
    case DXGI_FORMAT_R32_UINT:
        HeapProperties = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT);
        Desc = CD3DX12_RESOURCE_DESC::Buffer(sizeof(UINT) * s备用资料->索引.size());
        设备->CreateCommittedResource(
            &HeapProperties,
            D3D12_HEAP_FLAG_NONE,
            &Desc,
            D3D12_RESOURCE_STATE_COMMON,
            nullptr,
            IID_PPV_ARGS(&索引));

        HeapProperties = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
        Desc = CD3DX12_RESOURCE_DESC::Buffer(sizeof(UINT) * s备用资料->索引.size());
        设备->CreateCommittedResource(
            &HeapProperties,
            D3D12_HEAP_FLAG_NONE,
            &Desc,
            D3D12_RESOURCE_STATE_GENERIC_READ,
            nullptr,
            IID_PPV_ARGS(&索引上传));

        ibv.SizeInBytes = sizeof(UINT) * 索引数量;
        ibv.Format = DXGI_FORMAT_R32_UINT;
        break;

    case DXGI_FORMAT_R16_UINT:
        HeapProperties = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT);
        Desc = CD3DX12_RESOURCE_DESC::Buffer(sizeof(USHORT) * s备用资料->s索引.size());
        设备->CreateCommittedResource(
            &HeapProperties,
            D3D12_HEAP_FLAG_NONE,
            &Desc,
            D3D12_RESOURCE_STATE_COMMON,
            nullptr,
            IID_PPV_ARGS(&索引));

        HeapProperties = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
        Desc = CD3DX12_RESOURCE_DESC::Buffer(sizeof(USHORT) * s备用资料->s索引.size());
        设备->CreateCommittedResource(
            &HeapProperties,
            D3D12_HEAP_FLAG_NONE,
            &Desc,
            D3D12_RESOURCE_STATE_GENERIC_READ,
            nullptr,
            IID_PPV_ARGS(&索引上传));

        ibv.SizeInBytes = sizeof(USHORT) * 索引数量;
        ibv.Format = DXGI_FORMAT_R16_UINT;
        break;

    default:

        break;
    }

    if (索引格式 == DXGI_FORMAT_R16_UINT)
    {
        subResourceData.RowPitch = sizeof(USHORT) * s备用资料->s索引.size();
        subResourceData.pData = s备用资料->s索引.data();
    }
    else if(索引格式 == DXGI_FORMAT_R32_UINT)
    {
        subResourceData.RowPitch = sizeof(UINT) * s备用资料->索引.size();
        subResourceData.pData = s备用资料->索引.data();
    }

    subResourceData.SlicePitch = subResourceData.RowPitch;

    pBarriers = CD3DX12_RESOURCE_BARRIER::Transition(索引.Get(),
        D3D12_RESOURCE_STATE_COMMON, D3D12_RESOURCE_STATE_COPY_DEST);
    命令队列->ResourceBarrier(1, &pBarriers);
    UpdateSubresources<1>(命令队列.Get(), 索引.Get(), 索引上传.Get(), 0, 0, 1, &subResourceData);
    pBarriers = CD3DX12_RESOURCE_BARRIER::Transition(索引.Get(),
        D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_GENERIC_READ);
    命令队列->ResourceBarrier(1, &pBarriers);

    ibv.BufferLocation = 索引->GetGPUVirtualAddress();

    创建包围框缓存();
    生成纹理描述符();
}

//加载fbx静态文件-----------------------------------------------------------------------------------
void C静态物体::加载FBX文件(const WCHAR* 文件路径, wstring 物体名称键, DXGI_FORMAT 索引格式, float 体素粒度)
{
    FbxManager* lFBX管理 = NULL;
    FbxScene* l场景 = NULL;

    this->索引格式 = 索引格式;
    this->物体名称键 = 物体名称键;

    s备用资料 = new S备用资料;

    lFBX管理 = FbxManager::Create();
    FbxIOSettings* 输入 = FbxIOSettings::Create(lFBX管理, IOSROOT);
    lFBX管理->SetIOSettings(输入);
    FbxImporter* l导入 = FbxImporter::Create(lFBX管理, "");

    char* 文件名字 = 0;
    FbxWCToUTF8(文件路径, 文件名字, 0);
    if (!l导入->Initialize(文件名字, -1, 输入))
    {
        char 错误[100];
        sprintf_s(错误, "fbx导入错误: %s, line:%d\n", l导入->GetStatus().GetErrorString(), __LINE__);
        OutputDebugStringA(错误);
        PostQuitMessage(0);
        return;
    }

    l场景 = FbxScene::Create(lFBX管理, "myScene");
    l导入->Import(l场景);
    l导入->Destroy();

    FbxNode* 根节点 = l场景->GetRootNode();
    属性 = new C网格属性;
    属性->纹理集.resize(1);
    属性->纹理集[0] = nullptr;
    属性->纹理集上传.resize(1);
    属性->纹理集上传[0] = nullptr;
    属性->法线贴图集.resize(1);
    属性->法线贴图集[0] = nullptr;
    if (根节点)
    {
        for (int i = 0; i < 根节点->GetChildCount(); i++)
            加载节点(根节点->GetChild(i));
    }

    优化顶点();
    for (int i = 0; i < m控制顶点集.size(); i++)
        释放链表(m控制顶点集[i]);

    s备用资料->顶点集.resize(m优化顶点集.size());
    for (int i = 0; i < m优化顶点集.size(); i++)
    {
        s备用资料->顶点集[i] = m优化顶点集[i].顶点;
    }

    顶点数量 = s备用资料->顶点集.size();

    D3D12_HEAP_PROPERTIES HeapProperties = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT);
    D3D12_RESOURCE_DESC Desc = CD3DX12_RESOURCE_DESC::Buffer(sizeof(S顶点) * s备用资料->顶点集.size());
    设备->CreateCommittedResource(
        &HeapProperties,
        D3D12_HEAP_FLAG_NONE,
        &Desc,
        D3D12_RESOURCE_STATE_COMMON,
        nullptr,
        IID_PPV_ARGS(&顶点));

    HeapProperties = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
    Desc = CD3DX12_RESOURCE_DESC::Buffer(sizeof(S顶点) * s备用资料->顶点集.size());
    设备->CreateCommittedResource(
        &HeapProperties,
        D3D12_HEAP_FLAG_NONE,
        &Desc,
        D3D12_RESOURCE_STATE_GENERIC_READ,
        nullptr,
        IID_PPV_ARGS(&顶点上传));

    D3D12_SUBRESOURCE_DATA subResourceData = {};
    subResourceData.pData = s备用资料->顶点集.data();
    subResourceData.RowPitch = sizeof(S顶点) * s备用资料->顶点集.size();
    subResourceData.SlicePitch = subResourceData.RowPitch;

    D3D12_RESOURCE_BARRIER pBarriers = CD3DX12_RESOURCE_BARRIER::Transition(顶点.Get(),
        D3D12_RESOURCE_STATE_COMMON, D3D12_RESOURCE_STATE_COPY_DEST);
    命令队列->ResourceBarrier(1, &pBarriers);
    UpdateSubresources<1>(命令队列.Get(), 顶点.Get(), 顶点上传.Get(), 0, 0, 1, &subResourceData);
    pBarriers = CD3DX12_RESOURCE_BARRIER::Transition(顶点.Get(),
        D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_GENERIC_READ);
    命令队列->ResourceBarrier(1, &pBarriers);

    vbv.BufferLocation = 顶点->GetGPUVirtualAddress();
    vbv.StrideInBytes = sizeof(S顶点);
    vbv.SizeInBytes = sizeof(S顶点) * s备用资料->顶点集.size();

    switch (索引格式)
    {
    case DXGI_FORMAT_R32_UINT:
        HeapProperties = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT);
        Desc = CD3DX12_RESOURCE_DESC::Buffer(sizeof(UINT) * s备用资料->索引.size());
        设备->CreateCommittedResource(
            &HeapProperties,
            D3D12_HEAP_FLAG_NONE,
            &Desc,
            D3D12_RESOURCE_STATE_COMMON,
            nullptr,
            IID_PPV_ARGS(&索引));

        HeapProperties = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
        Desc = CD3DX12_RESOURCE_DESC::Buffer(sizeof(UINT) * s备用资料->索引.size());
        设备->CreateCommittedResource(
            &HeapProperties,
            D3D12_HEAP_FLAG_NONE,
            &Desc,
            D3D12_RESOURCE_STATE_GENERIC_READ,
            nullptr,
            IID_PPV_ARGS(&索引上传));

        ibv.SizeInBytes = sizeof(UINT) * 索引数量;
        ibv.Format = DXGI_FORMAT_R32_UINT;
        break;

    case DXGI_FORMAT_R16_UINT:
        HeapProperties = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT);
        Desc = CD3DX12_RESOURCE_DESC::Buffer(sizeof(USHORT) * s备用资料->索引.size());
        设备->CreateCommittedResource(
            &HeapProperties,
            D3D12_HEAP_FLAG_NONE,
            &Desc,
            D3D12_RESOURCE_STATE_COMMON,
            nullptr,
            IID_PPV_ARGS(&索引));

        HeapProperties = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
        Desc = CD3DX12_RESOURCE_DESC::Buffer(sizeof(USHORT) * s备用资料->索引.size());
        设备->CreateCommittedResource(
            &HeapProperties,
            D3D12_HEAP_FLAG_NONE,
            &Desc,
            D3D12_RESOURCE_STATE_GENERIC_READ,
            nullptr,
            IID_PPV_ARGS(&索引上传));

        ibv.SizeInBytes = sizeof(USHORT) * 索引数量;
        ibv.Format = DXGI_FORMAT_R16_UINT;
        break;

    default:

        break;
    }

    if (索引格式 == DXGI_FORMAT_R16_UINT)
    {
        s备用资料->s索引.resize(s备用资料->索引.size());
        for (int i = 0; i < s备用资料->索引.size(); i++)
            s备用资料->s索引[i] = s备用资料->索引[i];
        subResourceData.pData = s备用资料->s索引.data();
        subResourceData.RowPitch = sizeof(USHORT) * s备用资料->s索引.size();
    }
    else if(索引格式 == DXGI_FORMAT_R32_UINT)
    {
        subResourceData.pData = s备用资料->索引.data();
        subResourceData.RowPitch = sizeof(UINT) * s备用资料->索引.size();
    }

    subResourceData.SlicePitch = subResourceData.RowPitch;

    pBarriers = CD3DX12_RESOURCE_BARRIER::Transition(索引.Get(),
        D3D12_RESOURCE_STATE_COMMON, D3D12_RESOURCE_STATE_COPY_DEST);
    命令队列->ResourceBarrier(1, &pBarriers);
    UpdateSubresources<1>(命令队列.Get(), 索引.Get(), 索引上传.Get(), 0, 0, 1, &subResourceData);
    pBarriers = CD3DX12_RESOURCE_BARRIER::Transition(索引.Get(),
        D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_GENERIC_READ);
    命令队列->ResourceBarrier(1, &pBarriers);

    ibv.BufferLocation = 索引->GetGPUVirtualAddress();

    体素化(体素粒度);
    创建包围框缓存();
    创建包围球();
    生成纹理描述符();

    释放合并信息();
    lFBX管理->Destroy();
}

void C静态物体::加载节点(FbxNode* p节点)
{
    FbxNodeAttribute::EType l节点属性{};

    if (p节点->GetNodeAttribute())
    {
        l节点属性 = p节点->GetNodeAttribute()->GetAttributeType();

        switch (l节点属性)
        {
        case FbxNodeAttribute::eSkeleton:

            break;

        case FbxNodeAttribute::eMesh:
            加载网格(p节点);
            break;

        default:
            break;
        }
    }

    for (int i = 0; i < p节点->GetChildCount(); ++i)
    {
        加载节点(p节点->GetChild(i));
    }
}

void C静态物体::加载节点(FbxScene* p场景)
{
    int i;
    FbxNode* p节点 = p场景->GetRootNode();

    if (p节点)
    {
        for (i = 0; i < p节点->GetChildCount(); i++)
        {
            加载节点(p节点->GetChild(i));
        }
    }
}

void C静态物体::加载网格(FbxNode* p网格节点)
{
    FbxMesh* p网格 = p网格节点->GetMesh();
    if (p网格 == NULL) return;
    int i = 0;
    int j = 0;
    int k = 0;

    UINT l当前索引数量 = 0;
    UINT l当前顶点计数 = 0;
    UINT l多边形数量 = p网格->GetPolygonCount();
    for (i = 0; i < l多边形数量; i++)
    {
        int 当前多边形顶点数量 = p网格->GetPolygonSize(i);
        索引数量 += (当前多边形顶点数量 - 2) * 3;
        l当前索引数量 += (当前多边形顶点数量 - 2) * 3;
    }

    s备用资料->索引.resize(索引数量);
    m控制顶点集.resize(m控制顶点集.size() + p网格->GetControlPointsCount());
    //初始化链表
    for (i = m控制顶点集.size() - p网格->GetControlPointsCount(); i < m控制顶点集.size(); i++)
        m控制顶点集[i] = new S顶点索引;

    for (i = 0; i < l多边形数量; i++)
    {
        UINT 多边形顶点数量 = 0;
        多边形顶点数量 = p网格->GetPolygonSize(i);
        for (j = 0; j < 多边形顶点数量; j++)
        {
            int l控制顶点索引 = p网格->GetPolygonVertex(i, j);
            int id;
            FbxVector4* l控制顶点 = p网格->GetControlPoints();
            S顶点 l顶点{};

            l顶点.位置.z = l控制顶点[l控制顶点索引].mData[0];
            l顶点.位置.x = l控制顶点[l控制顶点索引].mData[1];
            l顶点.位置.y = l控制顶点[l控制顶点索引].mData[2];

            FbxGeometryElementUV* p纹理坐标 = p网格->GetElementUV(0);

            if(p纹理坐标)
                switch (p纹理坐标->GetMappingMode())
                {
                case FbxGeometryElement::eByControlPoint:
                    switch (p纹理坐标->GetReferenceMode())
                    {
                    case FbxGeometryElement::eDirect:
                        l顶点.纹理坐标.x = p纹理坐标->GetDirectArray().GetAt(l控制顶点索引).mData[0];
                        l顶点.纹理坐标.y = 1.0f - p纹理坐标->GetDirectArray().GetAt(l控制顶点索引).mData[1];
                        break;

                    case FbxGeometryElement::eIndexToDirect:
                        id = p纹理坐标->GetIndexArray().GetAt(l控制顶点索引);
                        l顶点.纹理坐标.x = p纹理坐标->GetDirectArray().GetAt(id).mData[0];
                        l顶点.纹理坐标.y = 1.0f - p纹理坐标->GetDirectArray().GetAt(id).mData[1];
                        break;

                    default:
                        break;
                    }
                    break;

                case FbxGeometryElement::eByPolygonVertex:
                    switch (p纹理坐标->GetReferenceMode())
                    {
                    case FbxGeometryElement::eDirect:
                    case FbxGeometryElement::eIndexToDirect:
                        l顶点.纹理坐标.x = p纹理坐标->GetDirectArray().GetAt(p网格->GetTextureUVIndex(i, j)).mData[0];
                        l顶点.纹理坐标.y = 1.0f - p纹理坐标->GetDirectArray().GetAt(p网格->GetTextureUVIndex(i, j)).mData[1];
                        break;

                    default:
                        break;
                    }
                    break;
                }

            FbxGeometryElementNormal* p法向量 = p网格->GetElementNormal(0);
            switch (p法向量->GetMappingMode())
            {
            case FbxGeometryElement::eByControlPoint:
                switch (p法向量->GetReferenceMode())
                {
                case FbxGeometryElement::eDirect:
                    l顶点.法向量.z = p法向量->GetDirectArray().GetAt(l控制顶点索引).mData[0];
                    l顶点.法向量.x = p法向量->GetDirectArray().GetAt(l控制顶点索引).mData[1];
                    l顶点.法向量.y = p法向量->GetDirectArray().GetAt(l控制顶点索引).mData[2];
                    break;

                case FbxGeometryElement::eIndexToDirect:
                    id = p法向量->GetIndexArray().GetAt(l控制顶点索引);
                    l顶点.法向量.z = p法向量->GetDirectArray().GetAt(id).mData[0];
                    l顶点.法向量.x = p法向量->GetDirectArray().GetAt(id).mData[1];
                    l顶点.法向量.y = p法向量->GetDirectArray().GetAt(id).mData[2];
                    break;

                default:
                    break;
                }
                break;

            case FbxGeometryElement::eByPolygonVertex:
                switch (p法向量->GetReferenceMode())
                {
                case FbxGeometryElement::eDirect:
                    l顶点.法向量.z = p法向量->GetDirectArray().GetAt(l当前顶点计数).mData[0];
                    l顶点.法向量.x = p法向量->GetDirectArray().GetAt(l当前顶点计数).mData[1];
                    l顶点.法向量.y = p法向量->GetDirectArray().GetAt(l当前顶点计数).mData[2];
                    break;

                case FbxGeometryElement::eIndexToDirect:
                    id = p法向量->GetIndexArray().GetAt(l当前顶点计数);
                    l顶点.法向量.z = p法向量->GetDirectArray().GetAt(id).mData[0];
                    l顶点.法向量.x = p法向量->GetDirectArray().GetAt(id).mData[1];
                    l顶点.法向量.y = p法向量->GetDirectArray().GetAt(id).mData[2];
                    break;

                default:
                    break;
                }
                break;
            }

            添加顶点(m控制顶点集[m控制顶点集.size() - p网格->GetControlPointsCount() + l控制顶点索引], l顶点, m顶点计数);
            m顶点计数++;
            l当前顶点计数++;
        }

        for (k = 0; k < 多边形顶点数量 - 2; k++)
        {
            s备用资料->索引[m索引计数] = m顶点计数 - 多边形顶点数量;
            m索引计数++;
            s备用资料->索引[m索引计数] = m顶点计数 - k - 1;
            m索引计数++;
            s备用资料->索引[m索引计数] = m顶点计数 - k - 2;
            m索引计数++;
        }
    }

    C网格属性::S属性* 属性 = new C网格属性::S属性;

    加载材质(p网格节点, 属性);

    FbxMesh* l网格 = (FbxMesh*)p网格节点->GetNodeAttribute();

    属性->索引数量 = l当前索引数量;
    属性->起始索引 = m索引计数 - l当前索引数量;
    XMMATRIX 变换矩阵 = XMMatrixIdentity();
    变换矩阵 = XMMatrixScaling(p网格节点->LclScaling.Get().mData[1], p网格节点->LclScaling.Get().mData[2],
        p网格节点->LclScaling.Get().mData[0]);
    变换矩阵 *= XMMatrixRotationRollPitchYaw(p网格节点->LclRotation.Get().mData[1] * XM_PI / 180,
        p网格节点->LclRotation.Get().mData[2] * XM_PI / 180, p网格节点->LclRotation.Get().mData[0] * XM_PI / 180);
    变换矩阵 *= XMMatrixTranslation(-p网格节点->LclTranslation.Get().mData[2], p网格节点->LclTranslation.Get().mData[1],
        p网格节点->LclTranslation.Get().mData[0]);
    属性->变换 = 变换矩阵;

    WCHAR* 网格名称 = 0;
    FbxUTF8ToWC(p网格节点->GetName(), 网格名称, 0);
    属性->物体名称 = 网格名称;

    this->属性->添加元素(属性);
}

void C静态物体::添加顶点(S顶点索引* p链表头, S顶点& 顶点, UINT 索引)
{
    S顶点索引* p节点 = p链表头;

    while (p节点->p下一节点)
        p节点 = p节点->p下一节点;

    p节点->p下一节点 = new S顶点索引;
    p节点 = p节点->p下一节点;

    p节点->顶点 = 顶点;
    p节点->索引 = 索引;
    p节点->p下一节点 = 0;
}

void C静态物体::释放链表(S顶点索引* p链表头)
{
    S顶点索引* p节点 = p链表头;
    S顶点索引* p下一节点 = p节点->p下一节点;

    while (p下一节点)
    {
        p节点 = p下一节点;
        p下一节点 = p节点->p下一节点;
        delete p节点;
        p节点 = p下一节点;
    }

    delete p节点;
    delete p链表头;
}

void C静态物体::加载材质(FbxNode* p网格节点, C网格属性::S属性* 属性)
{
    FbxMesh* p网格 = p网格节点->GetMesh();
    WCHAR* 网格名称 = 0;
    FbxUTF8ToWC(p网格节点->GetName(), 网格名称, 0);
    属性->物体名称 = 网格名称;
    int 材质数量 = 0;

    this->属性->纹理集[0] = 共享资源->白贴图;

    if (p网格 && p网格节点)
    {
        材质数量 = p网格节点->GetMaterialCount();
    }

    if (材质数量 > 0)
    {
        for (int i = 0; i < 材质数量; i++)
        {
            FbxSurfaceMaterial* p表面材质 = p网格节点->GetMaterial(i);

            加载材质属性(p表面材质, 属性);
        }
    }
    else  //默认材质
    {
        属性->材质.漫反射 = { 1.0f, 1.0f, 1.0f, 1.0f };
        属性->材质.环境光 = { 0.0f, 0.0f, 0.0f, 1.0f };
        属性->材质.自发光 = { 0.0f, 0.0f, 0.0f, 1.0f };
        属性->材质.光泽度 = 2.0f;
        属性->材质.不透明度 = 1.0f;
        属性->材质.高光级别 = 1.0f;
        属性->纹理索引 = 0;
    }
}

void C静态物体::加载材质属性(FbxSurfaceMaterial* p表面材质, C网格属性::S属性* 属性)
{
    p表面材质->GetName();

    if (p表面材质->GetClassId().Is(FbxSurfacePhong::ClassId))
    {
        FbxDouble3 漫反射 = ((FbxSurfacePhong*)p表面材质)->Diffuse;
        属性->材质.漫反射.x = 漫反射.mData[0];
        属性->材质.漫反射.y = 漫反射.mData[1];
        属性->材质.漫反射.z = 漫反射.mData[2];

        FbxDouble3 自发光 = ((FbxSurfacePhong*)p表面材质)->Emissive;
        属性->材质.自发光.x = 自发光.mData[0];
        属性->材质.自发光.y = 自发光.mData[1];
        属性->材质.自发光.z = 自发光.mData[2];

        FbxDouble 不透明度 = 1.0 - ((FbxSurfacePhong*)p表面材质)->TransparencyFactor;
        属性->材质.漫反射.w = 不透明度;

        FbxDouble 光泽度 = ((FbxSurfacePhong*)p表面材质)->Shininess;
        属性->材质.光泽度 = 光泽度;

        FbxDouble 高光等级 = ((FbxSurfacePhong*)p表面材质)->SpecularFactor;
        属性->材质.高光级别 = 高光等级;
        if (属性->材质.高光级别 < 1)属性->材质.高光级别 = 1;

        FbxDouble 反射率 = 1.0 - ((FbxSurfacePhong*)p表面材质)->ReflectionFactor;
    }
    else if (p表面材质->GetClassId().Is(FbxSurfaceLambert::ClassId))
    {
        FbxDouble3 环境光 = ((FbxSurfaceLambert*)p表面材质)->Ambient;
        属性->材质.环境光.x = 环境光.mData[0];
        属性->材质.环境光.y = 环境光.mData[1];
        属性->材质.环境光.z = 环境光.mData[2];

        FbxDouble3 漫反射 = ((FbxSurfaceLambert*)p表面材质)->Diffuse;
        属性->材质.漫反射.x = 漫反射.mData[0];
        属性->材质.漫反射.y = 漫反射.mData[1];
        属性->材质.漫反射.z = 漫反射.mData[2];

        FbxDouble3 自发光 = ((FbxSurfaceLambert*)p表面材质)->Emissive;
        属性->材质.自发光.x = 自发光.mData[0];
        属性->材质.自发光.y = 自发光.mData[1];
        属性->材质.自发光.z = 自发光.mData[2];

        FbxDouble 不透明度 = 1.0 - ((FbxSurfaceLambert*)p表面材质)->TransparencyFactor;
        属性->材质.漫反射.w = 不透明度;
    }

    加载纹理(p表面材质, 属性);
}

void C静态物体::加载纹理(FbxSurfaceMaterial* p表面材质, C网格属性::S属性* 属性)
{
    int i;
    int k = 0;
    int 结果 = 1;

    for (i = 0; i < FbxLayerElement::sTypeTextureCount; i++)
    {
        FbxProperty 材质属性;
        材质属性 = p表面材质->FindProperty(FbxLayerElement::sTextureChannelNames[i]);
        if (材质属性.IsValid())
        {
            int textureCount = 材质属性.GetSrcObjectCount();

            for (int j = 0; j < textureCount; ++j)
            {
                FbxFileTexture* p纹理 = FbxCast<FbxFileTexture>(材质属性.GetSrcObject(j));
                if (p纹理)
                {
                    WCHAR* 路径 = 0;
                    FbxUTF8ToWC(p纹理->GetFileName(), 路径, 0);
                    for (k = 0; k < s备用资料->路径集.size(); k++)
                    {
                        if (s备用资料->路径集[k].compare(路径) == 0 && 属性->纹理索引 == 0)
                        {
                            属性->纹理索引 = k + 1;
                            break;
                        }
                    }

                    if (属性->纹理索引 == 0)
                    {
                        s备用资料->路径集.resize(s备用资料->路径集.size() + 1);
                        s备用资料->路径集[s备用资料->路径集.size() - 1] = 路径;

                        this->属性->纹理集.resize(this->属性->纹理集.size() + 1);
                        this->属性->纹理集上传.resize(this->属性->纹理集上传.size() + 1);
                        HRESULT hr = 0;

                        wstring 文件类型;
                        bool 是否启录 = 0;
                        for (int i = 0; i < wcslen(路径); i++)
                        {
                            if (是否启录) 文件类型 += 路径[i];
                            if (路径[i] == '.')
                            {
                                是否启录 = 1;
                                文件类型.clear();
                            }
                        }

                        if (文件类型 == L"dds")
                        {
                            if (!SUCCEEDED(hr = CreateDDSTextureFromFile12(设备.Get(), 命令队列.Get(), 路径,
                                this->属性->纹理集[this->属性->纹理集.size() - 1], this->属性->纹理集上传[this->属性->纹理集上传.size() - 1])))
                            {
                                wstring bug = L"加载模型材质时未找到贴图文件 line:" + to_wstring(__LINE__) + L'\n';
                                OutputDebugString(bug.c_str());
                                PostQuitMessage(0);
                            }
                        }
                        else
                        {
                            if (!SUCCEEDED(CreateImageDataTextureFromFile(设备.Get(), 命令队列.Get(), 路径, this->属性->纹理集[this->属性->纹理集.size() - 1],
                                this->属性->纹理集上传[this->属性->纹理集上传.size() - 1])))
                            {
                                wstring bug = L"加载模型材质时未找到贴图文件 line:";
                                bug += to_wstring(__LINE__) + L"\n";
                                OutputDebugString(bug.c_str());
                                PostQuitMessage(0);
                            }
                        }
                        属性->纹理索引 = this->属性->纹理集.size() - 1;
                    }
                }
            }
        }
    }
}

void C静态物体::优化顶点()
{
    float 最小cos角度 = cosf(法向量合并最大角度);
    UINT i = 0;
    UINT j = 0;
    UINT k = 0;

    for (i = 0; i < m控制顶点集.size(); i++)
    {
        合并顶点(m控制顶点集[i], 最小cos角度, 贴图顶点采样最大间隔);
    }

    for (i = 0; i < 索引数量; i++)
    {
        for (j = 0; j < m合并索引集.size(); j++)
        {
            for (k = 0; k < m合并索引集[j].副索引集.size(); k++)
            {
                if (s备用资料->索引[i] == m合并索引集[j].副索引集[k])
                {
                    s备用资料->索引[i] = m合并索引集[j].主索引;
                    goto 重新循环;
                }
            }
        }
    重新循环:
        continue;
    }
}

void C静态物体::合并顶点(S顶点索引* p链表头, float 最小cos角度, float 最大uv间隔)
{
    S顶点索引* p节点 = p链表头;
    UINT i = 0;
    UINT j = 0;
    UINT k = 0;

    UINT 节点数量 = 0;
    while (p节点->p下一节点)
    {
        p节点 = p节点->p下一节点;
        节点数量++;
    }
    vector<S优化顶点集> 顶点集;
    顶点集.resize(节点数量);

    UINT 当前顶点 = 0;
    p节点 = p链表头;
    while (p节点->p下一节点)
    {
        p节点 = p节点->p下一节点;
        顶点集[当前顶点].顶点 = p节点->顶点;
        顶点集[当前顶点].索引 = p节点->索引;
        当前顶点++;
    }

    XMVECTOR 法向量1, 法向量2;
    XMVECTOR 纹理1, 纹理2;

    for (i = 0; i < 节点数量; i++)
    {
        for (j = i + 1; j < 节点数量; j++)
        {
            法向量1 = XMLoadFloat3(&顶点集[i].顶点.法向量);
            法向量2 = XMLoadFloat3(&顶点集[j].顶点.法向量);
            纹理1 = XMLoadFloat2(&顶点集[i].顶点.纹理坐标);
            纹理2 = XMLoadFloat2(&顶点集[j].顶点.纹理坐标);

            if (XMVector3Dot(法向量1, 法向量2).m128_f32[0] < 最小cos角度 ||
                XMVector2Length(纹理1 - 纹理2).m128_f32[0] > 最大uv间隔)
            {
                for (k = 0; k < 节点数量; k++)
                {
                    m优化顶点集.resize(m优化顶点集.size() + 1);
                    m优化顶点集[m优化顶点集.size() - 1].顶点.位置 = 顶点集[k].顶点.位置;
                    m优化顶点集[m优化顶点集.size() - 1].顶点.法向量 = 顶点集[k].顶点.法向量;
                    m优化顶点集[m优化顶点集.size() - 1].顶点.纹理坐标 = 顶点集[k].顶点.纹理坐标;
                    m优化顶点集[m优化顶点集.size() - 1].索引 = 顶点集[k].索引;

                    m合并索引集.resize(m合并索引集.size() + 1);
                    m合并索引集[m合并索引集.size() - 1].主索引 = m优化顶点集.size() - 1;
                    m合并索引集[m合并索引集.size() - 1].副索引集.push_back(顶点集[k].索引);
                }
                goto 跳出;
            }
        }
    }

    m合并索引集.resize(m合并索引集.size() + 1);
    m合并索引集[m合并索引集.size() - 1].主索引 = m优化顶点集.size();
    m合并索引集[m合并索引集.size() - 1].副索引集.resize(节点数量);

    法向量1 = { 0.0f, 0.0f, 0.0f, 0.0f };
    for (i = 0; i < 节点数量; i++)
    {
        m合并索引集[m合并索引集.size() - 1].副索引集[i] = 顶点集[i].索引;
        法向量1 += XMLoadFloat3(&顶点集[i].顶点.法向量);
    }
    法向量1 = 法向量1 / 节点数量;

    m优化顶点集.resize(m优化顶点集.size() + 1);
    m优化顶点集[m优化顶点集.size() - 1].顶点.位置 = 顶点集[0].顶点.位置;
    XMStoreFloat3(&m优化顶点集[m优化顶点集.size() - 1].顶点.法向量, 法向量1);
    m优化顶点集[m优化顶点集.size() - 1].顶点.纹理坐标 = 顶点集[0].顶点.纹理坐标;
    m优化顶点集[m优化顶点集.size() - 1].索引 = 顶点集[0].索引;

跳出:
    return;
}

void C静态物体::体素化(float 粒度)
{
    vector<XMFLOAT3> 最上点;
    vector<XMFLOAT3> 最下点;
    vector<XMFLOAT3> 最左点;
    vector<XMFLOAT3> 最右点;
    vector<XMFLOAT3> 最前点;
    vector<XMFLOAT3> 最后点;
    UINT 变换计数 = 0;

    m体素块.resize(属性->元素.size());
    最上点.resize(属性->元素.size());
    最下点.resize(属性->元素.size());
    最左点.resize(属性->元素.size());
    最右点.resize(属性->元素.size());
    最前点.resize(属性->元素.size());
    最后点.resize(属性->元素.size());
    for (int i = 0; i < 属性->元素.size(); i++)
    {
        m体素块[i] = new S体素块;
        m体素块[i]->间隔 = (float)1 / 粒度;

        //边界检测
        最后点[i] = s备用资料->顶点集[i].位置;

        XMVECTOR v最后点 = { 最后点[i].x, 最后点[i].y, 最后点[i].z, 1.0f };
        v最后点 = XMVector3Transform(v最后点, 属性->元素[0]->变换);
        最后点[i].x = v最后点.m128_f32[0]; 最后点[i].y = v最后点.m128_f32[1]; 最后点[i].z = v最后点.m128_f32[2];
        最前点[i] = 最右点[i] = 最左点[i] = 最下点[i] = 最上点[i] = 最后点[i];

        XMFLOAT3 点{};

        if (索引格式 == DXGI_FORMAT_R32_UINT)
        {
            for (int j = 属性->元素[变换计数]->起始索引; j < 属性->元素[变换计数]->起始索引 + 属性->元素[变换计数]->索引数量; j++)
            {
                点 = s备用资料->顶点集[s备用资料->索引[j]].位置;

                if (最上点[i].y < 点.y) 最上点[i] = 点;
                if (最下点[i].y > 点.y) 最下点[i] = 点;
                if (最左点[i].z > 点.z) 最左点[i] = 点;
                if (最右点[i].z < 点.z) 最右点[i] = 点;
                if (最前点[i].x > 点.x) 最前点[i] = 点;
                if (最后点[i].x < 点.x) 最后点[i] = 点;
            }

            变换计数++;
        }
        else if (索引格式 == DXGI_FORMAT_R16_UINT)
        {
            for (int j = 属性->元素[变换计数]->起始索引; j < 属性->元素[变换计数]->起始索引 + 属性->元素[变换计数]->索引数量; j++)
            {
                点 = s备用资料->顶点集[s备用资料->s索引[j]].位置;

                if (最上点[i].y < 点.y) 最上点[i] = 点;
                if (最下点[i].y > 点.y) 最下点[i] = 点;
                if (最左点[i].z > 点.z) 最左点[i] = 点;
                if (最右点[i].z < 点.z) 最右点[i] = 点;
                if (最前点[i].x > 点.x) 最前点[i] = 点;
                if (最后点[i].x < 点.x) 最后点[i] = 点;
            }

            变换计数++;
        }

        int 长 = 0;
        长 = (int)最后点[i].x - (int)最前点[i].x + 2;

        int 高 = 0;
        高 = (int)最上点[i].y - (int)最下点[i].y + 2;

        int 宽 = 0;
        宽 = (int)最右点[i].z - (int)最左点[i].z + 2;

        m体素块[i]->边个数[0] = 长 * 粒度;  m体素块[i]->边个数[1] = 高 * 粒度;  m体素块[i]->边个数[2] = 宽 * 粒度;

        m体素块[i]->体素 = new bool** [m体素块[i]->边个数[2]];
        for (int m = 0; m < m体素块[i]->边个数[2]; m++)
        {
            m体素块[i]->体素[m] = new bool* [m体素块[i]->边个数[1]];
            for (int j = 0; j < m体素块[i]->边个数[1]; j++)
            {
                m体素块[i]->体素[m][j] = new bool[m体素块[i]->边个数[0]];
                for (int k = 0; k < m体素块[i]->边个数[0]; k++)
                    m体素块[i]->体素[m][j][k] = 0;
            }
        }
    }

    for(int i = 0; i < 属性->元素.size(); i++)
    {
        float 间隔 = 1.0f / 粒度;

        m体素块[i]->左下角位置.z = (float)(int)(最左点[i].z - 1); m体素块[i]->左下角位置.y = (float)(int)(最下点[i].y - 1);
        m体素块[i]->左下角位置.x = (float)(int)(最前点[i].x - 1);

        //采样
        XMFLOAT3 采样点 = XMFLOAT3{ m体素块[i]->左下角位置.x, m体素块[i]->左下角位置.y, m体素块[i]->左下角位置.z };
        变换计数 = 0;
        int 线程数 = thread::hardware_concurrency();
        vector<thread> 线程;
        线程.resize(线程数);
        UINT 计数 = 0;

        if (索引格式 == DXGI_FORMAT_R32_UINT)
        {
            for (int z = 0; z < m体素块[i]->边个数[2]; z++)
            {
                采样点.y = m体素块[i]->左下角位置.y;
                for (int y = 0; y < m体素块[i]->边个数[1]; y++)
                {
                    采样点.x = m体素块[i]->左下角位置.x;
                    for (int x = 0; x < m体素块[i]->边个数[0]; x++)
                    {
                        线程[计数] = thread(体素采样线程, s备用资料, 属性, m体素块, 采样点, i, x, y, z);
                        计数++;

                        if (计数 == 线程数)
                        {
                            计数 = 0;
                            for (int n = 0; n < 线程数; n++)
                                if (线程[n].joinable()) 线程[n].join();
                        }

                        采样点.x += 间隔;
                    }
                    采样点.y += 间隔;
                }
                采样点.z += 间隔;
            }
        }
        else if (索引格式 == DXGI_FORMAT_R16_UINT)
        {
            for (int z = 0; z < m体素块[i]->边个数[2]; z++)
            {
                采样点.y = m体素块[i]->左下角位置.y;
                for (int y = 0; y < m体素块[i]->边个数[1]; y++)
                {
                    采样点.x = m体素块[i]->左下角位置.x;
                    for (int x = 0; x < m体素块[i]->边个数[0]; x++)
                    {
                        线程[计数] = thread(体素采样线程1, s备用资料, 属性, m体素块, 采样点, i, x, y, z);
                        计数++;

                        if (计数 == 线程数)
                        {
                            计数 = 0;
                            for (int n = 0; n < 线程数; n++)
                                if (线程[n].joinable()) 线程[n].join();
                        }

                        采样点.x += 间隔;
                    }
                    采样点.y += 间隔;
                }
                采样点.z += 间隔;
            }
        }

        for (int n = 0; n < 线程数; n++)
        {
            if (线程[n].joinable()) 线程[n].join();
        }
    }

    vector<bool***> 测试体素块;
    测试体素块.resize(m体素块.size());
    s备用资料->包围框块.resize(m体素块.size());

    for (int n = 0; n < m体素块.size(); n++)
    {
        测试体素块[n] = new bool** [m体素块[n]->边个数[2]];
        for (int i = 0; i < m体素块[n]->边个数[2]; i++)
        {
            测试体素块[n][i] = new bool* [m体素块[n]->边个数[1]];
            for (int j = 0; j < m体素块[n]->边个数[1]; j++)
            {
                测试体素块[n][i][j] = new bool[m体素块[n]->边个数[0]];
                for (int k = 0; k < m体素块[n]->边个数[0]; k++)
                    测试体素块[n][i][j][k] = m体素块[n]->体素[i][j][k];
            }
        }

        vector<S体素位> 体素位集;
        bool 是否有空 = 1;

        while (是否有空)
        {
            是否有空 = 0;
            for (int z = 0; z < m体素块[n]->边个数[2]; z++)
            {
                for (int y = 0; y < m体素块[n]->边个数[1]; y++)
                {
                    for (int x = 0; x < m体素块[n]->边个数[0]; x++)
                    {
                        if (测试体素块[n][z][y][x])
                        {
                            UINT 位置 = 体素位集.size();
                            体素位集.resize(体素位集.size() + 1);
                            体素位集[位置].x = x;
                            体素位集[位置].y = y;
                            体素位集[位置].z = z;
                            是否有空 = 1;

                            while (x - (int)体素位集[位置].前上左 - 1 >= 0 && y + (int)体素位集[位置].前上左 + 1 < m体素块[n]->边个数[1]
                                && z - (int)体素位集[位置].前上左 - 1 >= 0)
                            {
                                if (测试体素块[n][z - 体素位集[位置].前上左 - 1][y + 体素位集[位置].前上左 + 1][x - 体素位集[位置].前上左 - 1])
                                {
                                    体素位集[位置].前上左++;
                                }
                                else break;
                            }

                            while (x - (int)体素位集[位置].前上右 - 1 >= 0 && y + (int)体素位集[位置].前上右 + 1 < m体素块[n]->边个数[1]
                                && z + (int)体素位集[位置].前上右 + 1 < m体素块[n]->边个数[2])
                            {
                                if (测试体素块[n][z + 体素位集[位置].前上右 + 1][y + 体素位集[位置].前上右 + 1][x - 体素位集[位置].前上右 - 1])
                                {
                                    体素位集[位置].前上右++;
                                }
                                else break;
                            }

                            while (x - (int)体素位集[位置].前下左 - 1 >= 0 && y - (int)体素位集[位置].前下左 - 1 >= 0
                                && z - (int)体素位集[位置].前下左 - 1 >= 0)
                            {
                                if (测试体素块[n][z - 体素位集[位置].前下左 - 1][y - 体素位集[位置].前下左 - 1][x - 体素位集[位置].前下左 - 1])
                                {
                                    体素位集[位置].前下左++;
                                }
                                else break;
                            }

                            while (x - (int)体素位集[位置].前下右 - 1 >= 0 && y - (int)体素位集[位置].前下右 - 1 >= 0
                                && z + (int)体素位集[位置].前下右 + 1 < m体素块[n]->边个数[2])
                            {
                                if (测试体素块[n][z + 体素位集[位置].前下右 + 1][y - 体素位集[位置].前下右 - 1][x - 体素位集[位置].前下右 - 1])
                                {
                                    体素位集[位置].前下右++;
                                }
                                else break;
                            }

                            while (x + (int)体素位集[位置].后上左 + 1 < m体素块[n]->边个数[0] && y + (int)体素位集[位置].后上左 + 1 < m体素块[n]->边个数[1]
                                && z - (int)体素位集[位置].后上左 - 1 >= 0)
                            {
                                if (测试体素块[n][z - 体素位集[位置].后上左 - 1][y + 体素位集[位置].后上左 + 1][x + 体素位集[位置].后上左 + 1])
                                {
                                    体素位集[位置].后上左++;
                                }
                                else break;
                            }

                            while (x + (int)体素位集[位置].后上右 + 1 < m体素块[n]->边个数[0] && y + (int)体素位集[位置].后上右 + 1 < m体素块[n]->边个数[1]
                                && z + (int)体素位集[位置].后上右 + 1 < m体素块[n]->边个数[2])
                            {
                                if (测试体素块[n][z + 体素位集[位置].后上右 + 1][y + 体素位集[位置].后上右 + 1][x + 体素位集[位置].后上右 + 1])
                                {
                                    体素位集[位置].后上右++;
                                }
                                else break;
                            }

                            while (x + (int)体素位集[位置].后下左 + 1 < m体素块[n]->边个数[0] && y - (int)体素位集[位置].后下左 - 1 >= 0
                                && z - (int)体素位集[位置].后下左 - 1 >= 0)
                            {
                                if (测试体素块[n][z - 体素位集[位置].后下左 - 1][y - 体素位集[位置].后下左 - 1][x + 体素位集[位置].后下左 + 1])
                                {
                                    体素位集[位置].后下左++;
                                }
                                else break;
                            }

                            while (x + (int)体素位集[位置].后下右 + 1 < m体素块[n]->边个数[0] && y - (int)体素位集[位置].后下右 - 1 >= 0
                                && z + (int)体素位集[位置].后下右 + 1 < m体素块[n]->边个数[2])
                            {
                                if (测试体素块[n][z + 体素位集[位置].后下右 + 1][y - 体素位集[位置].后下右 - 1][x + 体素位集[位置].后下右 + 1])
                                {
                                    体素位集[位置].后下右++;
                                }
                                else break;
                            }
                        }
                    }
                }
            }

            UINT 最大位 = 0;
            UINT 最小数 = 0;
            UINT 最大数 = 0;
            for (int i = 0; i < 体素位集.size(); i++)
            {
                UINT 最小数 = UINT32_MAX;
                if (最小数 > 体素位集[i].前上右) 最小数 = 体素位集[i].前上右;
                if (最小数 > 体素位集[i].前上左) 最小数 = 体素位集[i].前上左;
                if (最小数 > 体素位集[i].前下右) 最小数 = 体素位集[i].前下右;
                if (最小数 > 体素位集[i].前下左) 最小数 = 体素位集[i].前下左;
                if (最小数 > 体素位集[i].后上右) 最小数 = 体素位集[i].后上右;
                if (最小数 > 体素位集[i].后上左) 最小数 = 体素位集[i].后上左;
                if (最小数 > 体素位集[i].后下右) 最小数 = 体素位集[i].后下右;
                if (最小数 > 体素位集[i].后下左) 最小数 = 体素位集[i].后下左;

                if (最小数 > 最大数)
                {
                    最大数 = 最小数;
                    最大位 = i;
                }
                else if (最大数 = 最小数)
                {
                    mt19937 mt(rd());
                    UINT 随机数 = mt() % 1;
                    if (随机数) 最大位 = i;
                }
            }

            if (体素位集.size() != 0)
            {
                UINT 延伸位 = 体素位集[最大位].前上右;
                UINT 最大位x = 体素位集[最大位].x;
                UINT 最大位y = 体素位集[最大位].y;
                UINT 最大位z = 体素位集[最大位].z;

                if (延伸位 > 体素位集[最大位].前上左) 延伸位 = 体素位集[最大位].前上左;
                if (延伸位 > 体素位集[最大位].前下右) 延伸位 = 体素位集[最大位].前下右;
                if (延伸位 > 体素位集[最大位].前下左) 延伸位 = 体素位集[最大位].前下左;
                if (延伸位 > 体素位集[最大位].后上右) 延伸位 = 体素位集[最大位].后上右;
                if (延伸位 > 体素位集[最大位].后上左) 延伸位 = 体素位集[最大位].后上左;
                if (延伸位 > 体素位集[最大位].后下右) 延伸位 = 体素位集[最大位].后下右;
                if (延伸位 > 体素位集[最大位].后下左) 延伸位 = 体素位集[最大位].后下左;

                for (int k = 最大位z - 延伸位; k <= 最大位z + 延伸位; k++)
                {
                    for (int j = 最大位y - 延伸位; j <= 最大位y + 延伸位; j++)
                    {
                        for (int i = 最大位x - 延伸位; i <= 最大位x + 延伸位; i++)
                        {
                            测试体素块[n][k][j][i] = 0;
                        }
                    }
                }

                UINT 当前位 = s备用资料->包围框块[n].size();
                s备用资料->包围框块[n].resize(s备用资料->包围框块[n].size() + 1);
                s备用资料->包围框块[n][当前位].左下前位置.x = m体素块[n]->左下角位置.x + (体素位集[最大位].x - 延伸位) * m体素块[n]->间隔;
                s备用资料->包围框块[n][当前位].左下前位置.y = m体素块[n]->左下角位置.y + (体素位集[最大位].y - 延伸位) * m体素块[n]->间隔;
                s备用资料->包围框块[n][当前位].左下前位置.z = m体素块[n]->左下角位置.z + (体素位集[最大位].z - 延伸位) * m体素块[n]->间隔;
                s备用资料->包围框块[n][当前位].边长.x = (float)(延伸位 * 2 + 1) * m体素块[n]->间隔;
                s备用资料->包围框块[n][当前位].边长.y = (float)(延伸位 * 2 + 1) * m体素块[n]->间隔;
                s备用资料->包围框块[n][当前位].边长.z = (float)(延伸位 * 2 + 1) * m体素块[n]->间隔;
            }

            体素位集.clear();
        }

        bool 是否有连接 = 1;
        while (是否有连接)
        {
            是否有连接 = 0;
            for (int i = 0; i < s备用资料->包围框块[n].size(); i++)
            {
                for (int j = i; j < s备用资料->包围框块[n].size(); j++)
                {
                    if (s备用资料->包围框块[n][i].左下前位置.x == s备用资料->包围框块[n][j].左下前位置.x && s备用资料->包围框块[n][i].左下前位置.y == s备用资料->包围框块[n][j].左下前位置.y
                        && s备用资料->包围框块[n][i].边长.x == s备用资料->包围框块[n][j].边长.x && s备用资料->包围框块[n][i].边长.y == s备用资料->包围框块[n][j].边长.y
                        && (s备用资料->包围框块[n][i].左下前位置.z + s备用资料->包围框块[n][i].边长.z == s备用资料->包围框块[n][j].左下前位置.z
                            || s备用资料->包围框块[n][j].左下前位置.z + s备用资料->包围框块[n][j].边长.z == s备用资料->包围框块[n][i].左下前位置.z))
                    {
                        是否有连接 = 1;
                        s备用资料->包围框块[n][i].边长.z += s备用资料->包围框块[n][j].边长.z;
                        if (s备用资料->包围框块[n][i].左下前位置.z > s备用资料->包围框块[n][j].左下前位置.z) s备用资料->包围框块[n][i].左下前位置.z = s备用资料->包围框块[n][j].左下前位置.z;

                        vector<S包围框>::iterator i包围框 = s备用资料->包围框块[n].begin();
                        i包围框 += j;
                        s备用资料->包围框块[n].erase(i包围框);

                        goto 结束循环;
                    }

                    if (s备用资料->包围框块[n][i].左下前位置.x == s备用资料->包围框块[n][j].左下前位置.x && s备用资料->包围框块[n][i].左下前位置.z == s备用资料->包围框块[n][j].左下前位置.z
                        && s备用资料->包围框块[n][i].边长.x == s备用资料->包围框块[n][j].边长.x && s备用资料->包围框块[n][i].边长.z == s备用资料->包围框块[n][j].边长.z
                        && (s备用资料->包围框块[n][i].左下前位置.y + s备用资料->包围框块[n][i].边长.y == s备用资料->包围框块[n][j].左下前位置.y
                            || s备用资料->包围框块[n][j].左下前位置.y + s备用资料->包围框块[n][j].边长.y == s备用资料->包围框块[n][i].左下前位置.y))
                    {
                        是否有连接 = 1;
                        s备用资料->包围框块[n][i].边长.y += s备用资料->包围框块[n][j].边长.y;
                        if (s备用资料->包围框块[n][i].左下前位置.y > s备用资料->包围框块[n][j].左下前位置.y) s备用资料->包围框块[n][i].左下前位置.y = s备用资料->包围框块[n][j].左下前位置.y;

                        vector<S包围框>::iterator i包围框 = s备用资料->包围框块[n].begin();
                        i包围框 += j;
                        s备用资料->包围框块[n].erase(i包围框);

                        goto 结束循环;
                    }

                    if (s备用资料->包围框块[n][i].左下前位置.y == s备用资料->包围框块[n][j].左下前位置.y && s备用资料->包围框块[n][i].左下前位置.z == s备用资料->包围框块[n][j].左下前位置.z
                        && s备用资料->包围框块[n][i].边长.y == s备用资料->包围框块[n][j].边长.y && s备用资料->包围框块[n][i].边长.z == s备用资料->包围框块[n][j].边长.z
                        && (s备用资料->包围框块[n][i].左下前位置.x + s备用资料->包围框块[n][i].边长.x == s备用资料->包围框块[n][j].左下前位置.x
                            || s备用资料->包围框块[n][j].左下前位置.x + s备用资料->包围框块[n][j].边长.x == s备用资料->包围框块[n][i].左下前位置.x))
                    {
                        是否有连接 = 1;
                        s备用资料->包围框块[n][i].边长.x += s备用资料->包围框块[n][j].边长.x;
                        if (s备用资料->包围框块[n][i].左下前位置.x > s备用资料->包围框块[n][j].左下前位置.x) s备用资料->包围框块[n][i].左下前位置.x = s备用资料->包围框块[n][j].左下前位置.x;

                        vector<S包围框>::iterator i包围框 = s备用资料->包围框块[n].begin();
                        i包围框 += j;
                        s备用资料->包围框块[n].erase(i包围框);

                        goto 结束循环;
                    }
                }
            }

        结束循环:if (0);
        }
    }

    for (int n = 0; n < m体素块.size(); n++)
    {
        for (int i = 0; i < m体素块[n]->边个数[2]; i++)
        {
            for (int j = 0; j < m体素块[n]->边个数[1]; j++)
            {
                delete[] 测试体素块[n][i][j];
            }
            delete[] 测试体素块[n][i];
        }
        delete[] 测试体素块[n];
    }
    测试体素块.~vector();

    for(int i = 0; i < m体素块.size(); i++)
        delete m体素块[i];
    m体素块.~vector();
}

void C静态物体::体素采样线程(S备用资料* s备用资料, C网格属性* 属性, vector<S体素块*> m体素块, XMFLOAT3 采样点, UINT 体素块索引, UINT x, UINT y, UINT z)
{
    bool 上测试 = 0;
    bool 下测试 = 0;
    bool 左测试 = 0;
    bool 右测试 = 0;
    bool 前测试 = 0;
    bool 后测试 = 0;
    UINT 变换计数;

    变换计数 = 0;

    for (int i = 0; i < s备用资料->s索引.size(); i = i + 3)
    {
        float 距离 = 0;
        XMVECTOR 原点{};
        XMVECTOR 方向{};
        XMVECTOR 顶点1{};
        XMVECTOR 顶点2{};
        XMVECTOR 顶点3{};

        if (属性->元素[变换计数]->起始索引 + 属性->元素[变换计数]->索引数量 <= i)
        {
            变换计数++;
            上测试 = 0;
            下测试 = 0;
            左测试 = 0;
            右测试 = 0;
            前测试 = 0;
            后测试 = 0;
        }
        if (变换计数 != 体素块索引) continue;

        原点.m128_f32[0] = 采样点.x; 原点.m128_f32[1] = 采样点.y; 原点.m128_f32[2] = 采样点.z;

        顶点1.m128_f32[0] = s备用资料->顶点集[s备用资料->s索引[i]].位置.x; 顶点1.m128_f32[1] = s备用资料->顶点集[s备用资料->s索引[i]].位置.y;
        顶点1.m128_f32[2] = s备用资料->顶点集[s备用资料->s索引[i]].位置.z;
        顶点2.m128_f32[0] = s备用资料->顶点集[s备用资料->s索引[i + 1]].位置.x; 顶点2.m128_f32[1] = s备用资料->顶点集[s备用资料->s索引[i + 1]].位置.y;
        顶点2.m128_f32[2] = s备用资料->顶点集[s备用资料->s索引[i + 1]].位置.z;
        顶点3.m128_f32[0] = s备用资料->顶点集[s备用资料->s索引[i + 2]].位置.x; 顶点3.m128_f32[1] = s备用资料->顶点集[s备用资料->s索引[i + 2]].位置.y;
        顶点3.m128_f32[2] = s备用资料->顶点集[s备用资料->s索引[i + 2]].位置.z;

        方向.m128_f32[0] = 1.0f; 方向.m128_f32[1] = 0.0f; 方向.m128_f32[2] = 0.0f;
        if (TriangleTests::Intersects(原点, 方向, 顶点1, 顶点2, 顶点3, 距离)) 后测试 = 1;
        方向.m128_f32[0] = -1.0f; 方向.m128_f32[1] = 0.0f; 方向.m128_f32[2] = 0.0f;
        if (TriangleTests::Intersects(原点, 方向, 顶点1, 顶点2, 顶点3, 距离)) 前测试 = 1;
        方向.m128_f32[0] = 0.0f; 方向.m128_f32[1] = 1.0f; 方向.m128_f32[2] = 0.0f;
        if (TriangleTests::Intersects(原点, 方向, 顶点1, 顶点2, 顶点3, 距离)) 上测试 = 1;
        方向.m128_f32[0] = 0.0f; 方向.m128_f32[1] = -1.0f; 方向.m128_f32[2] = 0.0f;
        if (TriangleTests::Intersects(原点, 方向, 顶点1, 顶点2, 顶点3, 距离)) 下测试 = 1;
        方向.m128_f32[0] = 0.0f; 方向.m128_f32[1] = 0.0f; 方向.m128_f32[2] = 1.0f;
        if (TriangleTests::Intersects(原点, 方向, 顶点1, 顶点2, 顶点3, 距离)) 右测试 = 1;
        方向.m128_f32[0] = 0.0f; 方向.m128_f32[1] = 0.0f; 方向.m128_f32[2] = -1.0f;
        if (TriangleTests::Intersects(原点, 方向, 顶点1, 顶点2, 顶点3, 距离)) 左测试 = 1;

        if (上测试 && 下测试 && 左测试 && 右测试 && 前测试 && 后测试)
        {
            m体素块[体素块索引]->体素[z][y][x] = 1;
        }
    }
}

void C静态物体::体素采样线程1(S备用资料* s备用资料, C网格属性* 属性, vector<S体素块*> m体素块, XMFLOAT3 采样点, UINT 体素块索引, UINT x, UINT y, UINT z)
{
    bool 上测试 = 0;
    bool 下测试 = 0;
    bool 左测试 = 0;
    bool 右测试 = 0;
    bool 前测试 = 0;
    bool 后测试 = 0;
    UINT 变换计数 = 0;

    for (int i = 0; i < s备用资料->索引.size(); i = i + 3)
    {
        float 距离 = 0;
        XMVECTOR 原点{};
        XMVECTOR 方向{};
        XMVECTOR 顶点1{};
        XMVECTOR 顶点2{};
        XMVECTOR 顶点3{};

        if (属性->元素[变换计数]->起始索引 + 属性->元素[变换计数]->索引数量 <= i)
        {
            变换计数++;
            上测试 = 0;
            下测试 = 0;
            左测试 = 0;
            右测试 = 0;
            前测试 = 0;
            后测试 = 0;
        }
        if (变换计数 != 体素块索引) continue;

        原点.m128_f32[0] = 采样点.x; 原点.m128_f32[1] = 采样点.y; 原点.m128_f32[2] = 采样点.z;

        顶点1.m128_f32[0] = s备用资料->顶点集[s备用资料->索引[i]].位置.x; 顶点1.m128_f32[1] = s备用资料->顶点集[s备用资料->索引[i]].位置.y;
        顶点1.m128_f32[2] = s备用资料->顶点集[s备用资料->索引[i]].位置.z;
        顶点2.m128_f32[0] = s备用资料->顶点集[s备用资料->索引[i + 1]].位置.x; 顶点2.m128_f32[1] = s备用资料->顶点集[s备用资料->索引[i + 1]].位置.y;
        顶点2.m128_f32[2] = s备用资料->顶点集[s备用资料->索引[i + 1]].位置.z;
        顶点3.m128_f32[0] = s备用资料->顶点集[s备用资料->索引[i + 2]].位置.x; 顶点3.m128_f32[1] = s备用资料->顶点集[s备用资料->索引[i + 2]].位置.y;
        顶点3.m128_f32[2] = s备用资料->顶点集[s备用资料->索引[i + 2]].位置.z;

        方向.m128_f32[0] = 1.0f; 方向.m128_f32[1] = 0.0f; 方向.m128_f32[2] = 0.0f;
        if (TriangleTests::Intersects(原点, 方向, 顶点1, 顶点2, 顶点3, 距离)) 后测试 = 1;
        方向.m128_f32[0] = -1.0f; 方向.m128_f32[1] = 0.0f; 方向.m128_f32[2] = 0.0f;
        if (TriangleTests::Intersects(原点, 方向, 顶点1, 顶点2, 顶点3, 距离)) 前测试 = 1;
        方向.m128_f32[0] = 0.0f; 方向.m128_f32[1] = 1.0f; 方向.m128_f32[2] = 0.0f;
        if (TriangleTests::Intersects(原点, 方向, 顶点1, 顶点2, 顶点3, 距离)) 上测试 = 1;
        方向.m128_f32[0] = 0.0f; 方向.m128_f32[1] = -1.0f; 方向.m128_f32[2] = 0.0f;
        if (TriangleTests::Intersects(原点, 方向, 顶点1, 顶点2, 顶点3, 距离)) 下测试 = 1;
        方向.m128_f32[0] = 0.0f; 方向.m128_f32[1] = 0.0f; 方向.m128_f32[2] = 1.0f;
        if (TriangleTests::Intersects(原点, 方向, 顶点1, 顶点2, 顶点3, 距离)) 右测试 = 1;
        方向.m128_f32[0] = 0.0f; 方向.m128_f32[1] = 0.0f; 方向.m128_f32[2] = -1.0f;
        if (TriangleTests::Intersects(原点, 方向, 顶点1, 顶点2, 顶点3, 距离)) 左测试 = 1;

        if (上测试 && 下测试 && 左测试 && 右测试 && 前测试 && 后测试)
        {
            m体素块[体素块索引]->体素[z][y][x] = 1;
        }
    }
}

void C静态物体::创建包围框缓存()
{
    for (int i = 0; i <属性->元素.size(); i++)
    {
        if (s备用资料->包围框块[i].size() != 0)
        {
            D3D12_HEAP_PROPERTIES HeapProperties = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT);
            D3D12_RESOURCE_DESC Desc = CD3DX12_RESOURCE_DESC::Buffer(sizeof(C静态物体::S包围框) * s备用资料->包围框块[i].size());
            设备->CreateCommittedResource(
                &HeapProperties,
                D3D12_HEAP_FLAG_NONE,
                &Desc,
                D3D12_RESOURCE_STATE_COMMON,
                nullptr,
                IID_PPV_ARGS(&属性->元素[i]->包围框));

            HeapProperties = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
            Desc = CD3DX12_RESOURCE_DESC::Buffer(sizeof(C静态物体::S包围框) * s备用资料->包围框块[i].size());
            设备->CreateCommittedResource(
                &HeapProperties,
                D3D12_HEAP_FLAG_NONE,
                &Desc,
                D3D12_RESOURCE_STATE_GENERIC_READ,
                nullptr,
                IID_PPV_ARGS(&属性->元素[i]->包围框上传));

            D3D12_SUBRESOURCE_DATA subResourceData = {};
            subResourceData.pData = s备用资料->包围框块[i].data();
            subResourceData.RowPitch = sizeof(C静态物体::S包围框) * s备用资料->包围框块[i].size();
            subResourceData.SlicePitch = subResourceData.RowPitch;

            D3D12_RESOURCE_BARRIER pBarriers = CD3DX12_RESOURCE_BARRIER::Transition(属性->元素[i]->包围框.Get(),
                D3D12_RESOURCE_STATE_COMMON, D3D12_RESOURCE_STATE_COPY_DEST);
            命令队列->ResourceBarrier(1, &pBarriers);
            UpdateSubresources<1>(命令队列.Get(), 属性->元素[i]->包围框.Get(), 属性->元素[i]->包围框上传.Get(), 0, 0, 1, &subResourceData);
            pBarriers = CD3DX12_RESOURCE_BARRIER::Transition(属性->元素[i]->包围框.Get(),
                D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_GENERIC_READ);
            命令队列->ResourceBarrier(1, &pBarriers);

            D3D12_SHADER_RESOURCE_VIEW_DESC* srvDesc = new D3D12_SHADER_RESOURCE_VIEW_DESC;
            srvDesc->Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
            srvDesc->Format = DXGI_FORMAT_UNKNOWN;
            srvDesc->ViewDimension = D3D12_SRV_DIMENSION_BUFFER;
            srvDesc->Buffer.Flags = D3D12_BUFFER_SRV_FLAG_NONE;
            srvDesc->Buffer.NumElements = s备用资料->包围框块[i].size();
            srvDesc->Buffer.StructureByteStride = sizeof(C静态物体::S包围框);
            srvDesc->Buffer.FirstElement = 0;

            描述符堆管理->加入srv描述符(属性->元素[i]->包围框, 物体名称键 + L"." + 属性->元素[i]->物体名称 + L"包围框srv", srvDesc);
        }

        D3D12_HEAP_PROPERTIES HeapProperties = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT);
        D3D12_RESOURCE_DESC Desc = CD3DX12_RESOURCE_DESC::Buffer(sizeof(S拾取输出),
            D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS);
        设备->CreateCommittedResource(
            &HeapProperties,
            D3D12_HEAP_FLAG_NONE,
            &Desc,
            D3D12_RESOURCE_STATE_COMMON,
            nullptr,
            IID_PPV_ARGS(&属性->元素[i]->拾取输出));

        HeapProperties = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
        Desc = CD3DX12_RESOURCE_DESC::Buffer(sizeof(S拾取输出));
        设备->CreateCommittedResource(
            &HeapProperties,
            D3D12_HEAP_FLAG_NONE,
            &Desc,
            D3D12_RESOURCE_STATE_GENERIC_READ,
            nullptr,
            IID_PPV_ARGS(&属性->元素[i]->拾取输出上传));

        S拾取输出 data{};
        D3D12_SUBRESOURCE_DATA subResourceData = {};
        subResourceData.pData = &data;
        subResourceData.RowPitch = sizeof(S拾取输出);
        subResourceData.SlicePitch = subResourceData.RowPitch;

        D3D12_RESOURCE_BARRIER pBarriers = CD3DX12_RESOURCE_BARRIER::Transition(属性->元素[i]->拾取输出.Get(),
            D3D12_RESOURCE_STATE_COMMON, D3D12_RESOURCE_STATE_COPY_DEST);
        命令队列->ResourceBarrier(1, &pBarriers);
        UpdateSubresources<1>(命令队列.Get(), 属性->元素[i]->拾取输出.Get(), 属性->元素[i]->拾取输出上传.Get(), 0, 0, 1, &subResourceData);
        pBarriers = CD3DX12_RESOURCE_BARRIER::Transition(属性->元素[i]->拾取输出.Get(),
            D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_UNORDERED_ACCESS);
        命令队列->ResourceBarrier(1, &pBarriers);

        D3D12_UNORDERED_ACCESS_VIEW_DESC* uavDesc = new D3D12_UNORDERED_ACCESS_VIEW_DESC;
        uavDesc->Format = DXGI_FORMAT_UNKNOWN;
        uavDesc->ViewDimension = D3D12_UAV_DIMENSION_BUFFER;
        uavDesc->Buffer.Flags = D3D12_BUFFER_UAV_FLAG_NONE;
        uavDesc->Buffer.NumElements = 1;
        uavDesc->Buffer.StructureByteStride = sizeof(S拾取输出);
        uavDesc->Buffer.FirstElement = 0;
        uavDesc->Buffer.CounterOffsetInBytes = 0;

        描述符堆管理->加入uav描述符(属性->元素[i]->拾取输出, 物体名称键 + L"." + 属性->元素[i]->物体名称 + L"拾取输出uav", uavDesc);
    }

    for (int i = 0; i < s备用资料->包围框块.size(); i++)
    {
        属性->元素[i]->包围框数量 = s备用资料->包围框块[i].size();
    }
}

void C静态物体::生成纹理描述符()
{
    D3D12_SHADER_RESOURCE_VIEW_DESC* srvDesc;

    for (int i = 0; i < 属性->元素.size(); i++)
    {
        srvDesc = new D3D12_SHADER_RESOURCE_VIEW_DESC;
        srvDesc->Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
        srvDesc->Format = 属性->纹理集[属性->元素[i]->纹理索引]->GetDesc().Format;
        srvDesc->ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
        srvDesc->Texture2D.MipLevels = 属性->纹理集[属性->元素[i]->纹理索引]->GetDesc().MipLevels;
        srvDesc->Texture2D.MostDetailedMip = 0;
        srvDesc->Texture2D.ResourceMinLODClamp = 0.0f;
        srvDesc->Texture2D.PlaneSlice = 0;

        描述符堆管理->加入srv描述符(属性->纹理集[属性->元素[i]->纹理索引], 物体名称键 + L"." + 属性->元素[i]->物体名称 + L"纹理srv", srvDesc);
    }
}

void C静态物体::创建包围球()
{
    XMVECTOR 中心点{};
    XMVECTOR 当前点{};
    float 最远距离 = 0;
    bool 初始化 = 0;

    for (int i = 0; i < 属性->元素.size(); i++)
    {
        if (索引格式 == DXGI_FORMAT_R32_UINT)
        {
            for (int j = 属性->元素[i]->起始索引; j < 属性->元素[i]->起始索引 + 属性->元素[i]->索引数量; j++)
            {
                中心点.m128_f32[0] += s备用资料->顶点集[s备用资料->索引[j]].位置.x; 中心点.m128_f32[1] += s备用资料->顶点集[s备用资料->索引[j]].位置.y;
                中心点.m128_f32[2] += s备用资料->顶点集[s备用资料->索引[j]].位置.z;
                if (初始化)
                {
                    中心点 /= 2;
                }
                初始化 = 1;
            }

            for (int j = 属性->元素[i]->起始索引; j < 属性->元素[i]->起始索引 + 属性->元素[i]->索引数量; j++)
            {
                当前点.m128_f32[0] = s备用资料->顶点集[s备用资料->索引[j]].位置.x; 当前点.m128_f32[1] = s备用资料->顶点集[s备用资料->索引[j]].位置.y;
                当前点.m128_f32[2] = s备用资料->顶点集[s备用资料->索引[j]].位置.z;
                if (XMVector3Length(当前点 - 中心点).m128_f32[0] > 最远距离)
                {
                    最远距离 = XMVector3Length(当前点 - 中心点).m128_f32[0];
                }
            }

            属性->元素[i]->包围球.Center.x = 中心点.m128_f32[0]; 属性->元素[i]->包围球.Center.y = 中心点.m128_f32[1];
            属性->元素[i]->包围球.Center.z = 中心点.m128_f32[2];
            属性->元素[i]->包围球.Radius = 最远距离;
        }
        else if (索引格式 == DXGI_FORMAT_R16_UINT)
        {
            for (int j = 属性->元素[i]->起始索引; j < 属性->元素[i]->起始索引 + 属性->元素[i]->索引数量; j++)
            {
                中心点.m128_f32[0] += s备用资料->顶点集[s备用资料->s索引[j]].位置.x; 中心点.m128_f32[1] += s备用资料->顶点集[s备用资料->s索引[j]].位置.y;
                中心点.m128_f32[2] += s备用资料->顶点集[s备用资料->s索引[j]].位置.z;
                if (初始化)
                {
                    中心点 /= 2;
                }
                初始化 = 1;
            }

            for (int j = 属性->元素[i]->起始索引; j < 属性->元素[i]->起始索引 + 属性->元素[i]->索引数量; j++)
            {
                当前点.m128_f32[0] = s备用资料->顶点集[s备用资料->s索引[j]].位置.x; 当前点.m128_f32[1] = s备用资料->顶点集[s备用资料->s索引[j]].位置.y;
                当前点.m128_f32[2] = s备用资料->顶点集[s备用资料->s索引[j]].位置.z;
                if (XMVector3Length(当前点 - 中心点).m128_f32[0] > 最远距离)
                {
                    最远距离 = XMVector3Length(当前点 - 中心点).m128_f32[0];
                }
            }

            属性->元素[i]->包围球.Center.x = 中心点.m128_f32[0]; 属性->元素[i]->包围球.Center.y = 中心点.m128_f32[1];
            属性->元素[i]->包围球.Center.z = 中心点.m128_f32[2];
            属性->元素[i]->包围球.Radius = 最远距离;
        }
    }
}

void C静态物体::绘制网格(UINT 属性)
{
    命令队列->IASetVertexBuffers(0, 1, &vbv);
    命令队列->IASetIndexBuffer(&ibv);
    命令队列->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    命令队列->DrawIndexedInstanced(this->属性->元素[属性]->索引数量, 1, this->属性->元素[属性]->起始索引, 0, 0);
}

void C静态物体::释放合并信息()
{
    m合并索引集.~vector();
    m控制顶点集.~vector();
}

C静态物体::~C静态物体()
{
    delete 属性;
    delete s备用资料;
}