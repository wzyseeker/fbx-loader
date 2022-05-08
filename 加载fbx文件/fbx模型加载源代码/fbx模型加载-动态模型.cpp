#include"fbx模型加载-动态模型.h"

C动态物体::C动态物体(ComPtr<ID3D12Device> 设备, ComPtr<ID3D12GraphicsCommandList> 命令队列, C描述符堆管理* 描述符堆管理, C共享资源* 共享资源)
{
    this->设备 = 设备;
    this->命令队列 = 命令队列;
    this->共享资源 = 共享资源;
    this->描述符堆管理 = 描述符堆管理;
}

//导出mdd文件-------------------------------------------------------------------
void C动态物体::导出mdd文件(wstring 文件名称)
{
    ofstream 输出文件;
    string 文件内容;
    string 图片名称;
    string 图片名称3;
    wstring 文件基础路径;
    WCHAR 图片名称w[128]{};
    char 图片名称1[128]{};
    string 图片名称2;
    UINT 字符串长度 = 0;
    UINT i = 0;
    UINT j = 0;
    UINT k = 0;

    for (int i = 0; i < 文件名称.size(); i++)
    {
        if (文件名称[i] == '.') break;
        文件基础路径 += 文件名称[i];
    }

    if (CreateDirectory(文件基础路径.c_str(), 0) == 0)
    {
        wstring bug = L"文件覆盖 line:" + to_wstring(__LINE__);
        bug += L"\n";
        OutputDebugString(bug.c_str());
    }

    WideCharToMultiByte(CP_ACP, 0, 文件基础路径.c_str(), 文件基础路径.size(), 图片名称1, 128, 0, 0);
    文件名称 = 文件基础路径 + L"\\" + 文件名称;

    输出文件.open(文件名称);

    if (!输出文件.is_open())
    {
        wstring bug = L"文件无法打开 line:" + to_wstring(__LINE__);
        bug += L"\n";
        OutputDebugString(bug.c_str());
        PostQuitMessage(0);
        return;
    }

    文件内容 = "属性数量：" + to_string(属性->元素.size()) + "；\n";
    输出文件.write(文件内容.c_str(), 文件内容.size());

    for (i = 0; i < s备用资料->路径集.size(); i++)
    {
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

        图片名称2 = 图片名称;
        图片名称3 = 图片名称1; 
        图片名称 = 图片名称3 + "\\" + 图片名称;

        int 长度 = MultiByteToWideChar(CP_ACP, 0, 图片名称.c_str(), 图片名称.size(), 图片名称w, 128);
        图片名称w[长度] = 0;

        CopyFile(s备用资料->路径集[i].c_str(), 图片名称w, TRUE);

        文件内容 = "材质名称：" + 图片名称2 + "；\n";
        输出文件.write(文件内容.c_str(), 文件内容.size());
    }

    文件内容 = "\n";
    输出文件.write(文件内容.c_str(), 文件内容.size());

    for (i = 0; i < 属性->元素.size(); i++)
    {
        char 物体名称[128]{};
        int 长度 = WideCharToMultiByte(CP_ACP, 0, 属性->元素[i]->物体名称.c_str(), 属性->元素[i]->物体名称.size(), 物体名称, 128, 0, 0);
        物体名称[长度] = 0;

        文件内容 = "网格属性.物体名称："; 文件内容 += 物体名称; 文件内容 += "；\n";
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
        文件内容 = "顶点.位置：" + to_string(s备用资料->顶点集[i].位置.x) + "；" +
            to_string(s备用资料->顶点集[i].位置.y) + "；" + to_string(s备用资料->顶点集[i].位置.z) + "；\n";
        输出文件.write(文件内容.c_str(), 文件内容.size());

        文件内容 = "顶点.法向量：" + to_string(s备用资料->顶点集[i].法向量.x) + "；" +
            to_string(s备用资料->顶点集[i].法向量.y) + "；" + to_string(s备用资料->顶点集[i].法向量.z) + "；\n";
        输出文件.write(文件内容.c_str(), 文件内容.size());

        文件内容 = "顶点.纹理：" + to_string(s备用资料->顶点集[i].纹理坐标.x) + "；" +
            to_string(s备用资料->顶点集[i].纹理坐标.y) + "；\n";
        输出文件.write(文件内容.c_str(), 文件内容.size());

        文件内容 = "顶点.关联骨骼索引：" + to_string(s备用资料->顶点集[i].关联骨骼索引[0]) + "；" +
            to_string(s备用资料->顶点集[i].关联骨骼索引[1]) + "；" + to_string(s备用资料->顶点集[i].关联骨骼索引[2]) 
            + "；" + to_string(s备用资料->顶点集[i].关联骨骼索引[2]) + "；\n";
        输出文件.write(文件内容.c_str(), 文件内容.size());

        文件内容 = "顶点.骨骼权重：" + to_string(s备用资料->顶点集[i].索引权重[0]) + "；" +
            to_string(s备用资料->顶点集[i].索引权重[1]) + "；" + to_string(s备用资料->顶点集[i].索引权重[2]) + "；\n";
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

    文件内容 = "\n轨道数量：" + to_string(动画轨道.size()) + "；\n";
    输出文件.write(文件内容.c_str(), 文件内容.size());

    文件内容 = "骨骼数量：" + to_string(骨骼数量) + "；\n";
    输出文件.write(文件内容.c_str(), 文件内容.size());

    for (i = 0; i < 动画轨道.size(); i++)
    {
        char 轨道名称[128]{};
        int 长度 = WideCharToMultiByte(CP_ACP, 0, 动画轨道[i].轨道名称.c_str(), 动画轨道[i].轨道名称.size(), 轨道名称, 128, 0, 0);
        轨道名称[长度] = 0;

        文件内容 = "动画轨道.轨道名称："; 文件内容 += 轨道名称; 文件内容 += "；\n";
        输出文件.write(文件内容.c_str(), 文件内容.size());

        文件内容 = "动画轨道.原始时长：" + to_string(动画轨道[i].原始时长) + "；\n";
        输出文件.write(文件内容.c_str(), 文件内容.size());

        文件内容 = "动画轨道.总帧数：" + to_string(动画轨道[i].帧.size()) + "；\n";
        输出文件.write(文件内容.c_str(), 文件内容.size());
        
        for (j = 0; j < 动画轨道[i].帧.size(); j++)
        {
            文件内容 = "动画轨道.物体数量：" + to_string(动画轨道[i].帧[j].物体变换.size()) + "；\n";
            输出文件.write(文件内容.c_str(), 文件内容.size());

            for (k = 0; k < 动画轨道[i].帧[j].物体变换.size(); k++)
            {
                文件内容 = "动画轨道.物体变换.变换：" + to_string(动画轨道[i].帧[j].物体变换[k].m[0][0]) + "；"
                    + to_string(动画轨道[i].帧[j].物体变换[k].m[0][1]) + "；" + to_string(动画轨道[i].帧[j].物体变换[k].m[0][2]) + "；"
                    + to_string(动画轨道[i].帧[j].物体变换[k].m[1][0]) + "；" + to_string(动画轨道[i].帧[j].物体变换[k].m[1][1]) + "；"
                    + to_string(动画轨道[i].帧[j].物体变换[k].m[1][2]) + "；" + to_string(动画轨道[i].帧[j].物体变换[k].m[2][0]) + "；"
                    + to_string(动画轨道[i].帧[j].物体变换[k].m[2][1]) + "；" + to_string(动画轨道[i].帧[j].物体变换[k].m[2][2]) + "；"
                    + to_string(动画轨道[i].帧[j].物体变换[k].m[3][0]) + "；" + to_string(动画轨道[i].帧[j].物体变换[k].m[3][1]) + "；"
                    + to_string(动画轨道[i].帧[j].物体变换[k].m[3][2]) + "；\n";
                输出文件.write(文件内容.c_str(), 文件内容.size());
            }

            文件内容 = "\n";
            输出文件.write(文件内容.c_str(), 文件内容.size());

            文件内容 = "动画轨道.骨骼数量：" + to_string(动画轨道[i].帧[j].骨骼变换.size()) + "；\n";
            输出文件.write(文件内容.c_str(), 文件内容.size());

            for (k = 0; k < 动画轨道[i].帧[j].骨骼变换.size(); k++)
            {
                文件内容 = "动画轨道.骨骼变换.变换：" + to_string(动画轨道[i].帧[j].骨骼变换[k].m[0][0]) + "；"
                    + to_string(动画轨道[i].帧[j].骨骼变换[k].m[0][1]) + "；" + to_string(动画轨道[i].帧[j].骨骼变换[k].m[0][2]) + "；"
                    + to_string(动画轨道[i].帧[j].骨骼变换[k].m[1][0]) + "；" + to_string(动画轨道[i].帧[j].骨骼变换[k].m[1][1]) + "；"
                    + to_string(动画轨道[i].帧[j].骨骼变换[k].m[1][2]) + "；" + to_string(动画轨道[i].帧[j].骨骼变换[k].m[2][0]) + "；"
                    + to_string(动画轨道[i].帧[j].骨骼变换[k].m[2][1]) + "；" + to_string(动画轨道[i].帧[j].骨骼变换[k].m[2][2]) + "；"
                    + to_string(动画轨道[i].帧[j].骨骼变换[k].m[3][0]) + "；" + to_string(动画轨道[i].帧[j].骨骼变换[k].m[3][1]) + "；"
                    + to_string(动画轨道[i].帧[j].骨骼变换[k].m[3][2]) + "；\n";
                输出文件.write(文件内容.c_str(), 文件内容.size());
            }

            文件内容 = "\n";
            输出文件.write(文件内容.c_str(), 文件内容.size());
        }
    }

    文件内容 = "\n";
    输出文件.write(文件内容.c_str(), 文件内容.size());

    输出文件.close();
}

//mdd文件加载---------------------------------------------------------------------

void C动态物体::导入mdd文件(wstring 文件名称, wstring 物体名称键)
{
    ifstream 输入文件;
    map<wstring, int> id;
    wstring 关键字 = L"";
    wstring 数值[20];
    UINT 步骤 = 0;
    UINT i = 0;
    UINT j = 0;
    char 数值2[128];
    char 内容[256];
    WCHAR 内容2[256];
    UINT 字符串长度 = 0;
    UINT 属性步骤 = 0;
    UINT 顶点步骤 = 0;
    UINT 索引步骤 = 0;
    wstring 基础路径;
    WCHAR 基础路径w[128]{};
    WCHAR 图片名称[128]{};
    UINT 轨道步骤 = 0;
    UINT 帧步骤 = 0;
    UINT 物体变换步骤 = 0;
    UINT 骨骼变换步骤 = 0;
    int 长度 = 0;
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
    id.insert(pair<wstring, int>(L"轨道数量", 23));
    id.insert(pair<wstring, int>(L"骨骼数量", 24));
    id.insert(pair<wstring, int>(L"动画轨道.轨道名称", 25));
    id.insert(pair<wstring, int>(L"动画轨道.原始时长", 26));
    id.insert(pair<wstring, int>(L"动画轨道.总帧数", 27));
    id.insert(pair<wstring, int>(L"动画轨道.物体数量", 28));
    id.insert(pair<wstring, int>(L"动画轨道.物体变换.变换", 29));
    id.insert(pair<wstring, int>(L"动画轨道.骨骼数量", 30));
    id.insert(pair<wstring, int>(L"动画轨道.骨骼变换.变换", 31));
    id.insert(pair<wstring, int>(L"顶点.关联骨骼索引", 32));
    id.insert(pair<wstring, int>(L"顶点.骨骼权重", 33));

    输入文件.open(文件名称);

    if (!输入文件.is_open())
    {
        wstring bug = L"文件无法打开 line:" + to_wstring(__LINE__);
        bug += L"\n";
        OutputDebugString(bug.c_str());
        PostQuitMessage(0);
        return;
    }

    s备用资料 = new S备用资料;

    while (!输入文件.eof())
    {
        关键字.clear();
        for (i = 0; i < 步骤; i++)
            数值[i].clear();
        步骤 = 0;

        输入文件.getline(内容, 256);
        字符串长度 = MultiByteToWideChar(CP_ACP, 0, 内容, strlen(内容), 内容2, 256);
        内容2[字符串长度] = 0;

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

        if (关键字[0] != '\0')
        switch (id[关键字])
        {
        case 0:
            属性 = new C网格属性;
            属性->元素.resize(stoi(数值[0]));
            for (int i = 0; i < 属性->元素.size(); i++)
            {
                属性->元素[i] = new C网格属性::S属性;
            }
            属性->纹理集.resize(1);
            属性->纹理集[0] = 共享资源->白贴图;
            属性->纹理集上传.resize(1);
            属性->纹理集上传[0] = nullptr;
            break;

        case 1:
            属性->元素[属性步骤]->物体名称 = 数值[0].c_str();
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
            属性->元素[属性步骤]->材质.漫反射.z = stof(数值[2]);
            break;

        case 8:
            属性->元素[属性步骤]->材质.自发光.x = stof(数值[0]); 属性->元素[属性步骤]->材质.自发光.y = stof(数值[1]);
            属性->元素[属性步骤]->材质.自发光.z = stof(数值[2]);
            break;

        case 9:
            属性->元素[属性步骤]->材质.环境光.x = stof(数值[0]); 属性->元素[属性步骤]->材质.环境光.y = stof(数值[1]);
            属性->元素[属性步骤]->材质.环境光.z = stof(数值[2]);
            break;

        case 10:
            属性->元素[属性步骤]->材质.光泽度 = stoi(数值[0]);
            break;

        case 11:
            属性->元素[属性步骤]->材质.高光级别 = stoi(数值[0]);
            break;

        case 12:
            属性->元素[属性步骤]->材质.不透明度 = stoi(数值[0]);
            属性步骤++;
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
            break;

        case 32:
            s备用资料->顶点集[顶点步骤].关联骨骼索引[0] = stof(数值[0]); s备用资料->顶点集[顶点步骤].关联骨骼索引[1] = stof(数值[1]);
            s备用资料->顶点集[顶点步骤].关联骨骼索引[2] = stof(数值[2]); s备用资料->顶点集[顶点步骤].关联骨骼索引[3] = stof(数值[3]);
            break;

        case 33:
            s备用资料->顶点集[顶点步骤].索引权重[0] = stof(数值[0]); s备用资料->顶点集[顶点步骤].索引权重[1] = stof(数值[1]);
            s备用资料->顶点集[顶点步骤].索引权重[2] = stof(数值[2]);
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
            for(int i = 0; i < 文件名称.size(); i++)
                图片名称[i] = 文件名称[i];
            图片名称[i] = L'\0';

            i = 文件名称.size();
            while (1)
            {
                if (图片名称[i] == L'/')
                {
                    图片名称[i] = L'\0';
                    break;
                }
                else if (图片名称[i] == L'\\')
                {
                    图片名称[i] = L'\0';
                    break;
                }
                i--;
            }
            基础路径 = 图片名称;

            基础路径 += L"\\";
            基础路径 += 数值[0].c_str();

            for (i = 0; i < s备用资料->路径集.size(); i++)
            {
                if (基础路径 == s备用资料->路径集[i])
                {
                    goto 跳出;
                }
            }
            s备用资料->路径集.push_back(基础路径);

            文件类型.clear();
            是否启录 = 0;
            for (int i = 0; i < 基础路径.size(); i++)
            {
                if (是否启录) 文件类型 += 基础路径[i];
                if (基础路径[i] == '.')
                {
                    是否启录 = 1;
                    文件类型.clear();
                }
            }

            属性->纹理集.resize(属性->纹理集.size() + 1);
            属性->纹理集上传.resize(属性->纹理集上传.size() + 1);
            if (文件类型 == L"dds")
            {
                if (!SUCCEEDED(CreateDDSTextureFromFile12(设备.Get(), 命令队列.Get(), 基础路径.c_str(), this->属性->纹理集[this->属性->纹理集.size() - 1],
                    this->属性->纹理集上传[this->属性->纹理集上传.size() - 1])))
                {
                    wstring bug = L"加载mdd文件时找不到贴图 line:" + to_wstring(__LINE__);
                    bug += L"\n";
                    OutputDebugString(bug.c_str());
                    PostQuitMessage(0);
                    return;
                }
            }
            else
            {
                if (!SUCCEEDED(CreateImageDataTextureFromFile(设备.Get(), 命令队列.Get(), 基础路径.c_str(), this->属性->纹理集[this->属性->纹理集.size() - 1],
                    this->属性->纹理集上传[this->属性->纹理集上传.size() - 1])))
                {
                    wstring bug = L"加载模型材质时未找到贴图文件 line:";
                    bug += to_wstring(__LINE__) + L"\n";
                    OutputDebugString(bug.c_str());
                    PostQuitMessage(0);
                    return;
                }
            }

        跳出:
            break;

        case 23:
            动画轨道.resize(stoi(数值[0]));
            break;

        case 24:
            骨骼数量 = stoi(数值[0]);
            break;

        case 25:
            帧步骤 = 0;
            动画轨道[轨道步骤].轨道名称 = 数值[0].c_str();
            轨道步骤++;
            break;

        case 26:
            动画轨道[轨道步骤 - 1].原始时长 = stof(数值[0]);
            break;

        case 27:
            动画轨道[轨道步骤 - 1].帧.resize(stoi(数值[0]));
            break;

        case 28:
            物体变换步骤 = 0;
            动画轨道[轨道步骤 - 1].帧[帧步骤].物体变换.resize(stoi(数值[0]));
            break;
        
        case 29:
            动画轨道[轨道步骤 - 1].帧[帧步骤].物体变换[物体变换步骤].m[0][0] = stof(数值[0]);
            动画轨道[轨道步骤 - 1].帧[帧步骤].物体变换[物体变换步骤].m[0][1] = stof(数值[1]);
            动画轨道[轨道步骤 - 1].帧[帧步骤].物体变换[物体变换步骤].m[0][2] = stof(数值[2]);
            动画轨道[轨道步骤 - 1].帧[帧步骤].物体变换[物体变换步骤].m[1][0] = stof(数值[3]);
            动画轨道[轨道步骤 - 1].帧[帧步骤].物体变换[物体变换步骤].m[1][1] = stof(数值[4]);
            动画轨道[轨道步骤 - 1].帧[帧步骤].物体变换[物体变换步骤].m[1][2] = stof(数值[5]);
            动画轨道[轨道步骤 - 1].帧[帧步骤].物体变换[物体变换步骤].m[2][0] = stof(数值[6]);
            动画轨道[轨道步骤 - 1].帧[帧步骤].物体变换[物体变换步骤].m[2][1] = stof(数值[7]);
            动画轨道[轨道步骤 - 1].帧[帧步骤].物体变换[物体变换步骤].m[2][2] = stof(数值[8]);
            动画轨道[轨道步骤 - 1].帧[帧步骤].物体变换[物体变换步骤].m[3][0] = stof(数值[9]);
            动画轨道[轨道步骤 - 1].帧[帧步骤].物体变换[物体变换步骤].m[3][1] = stof(数值[10]);
            动画轨道[轨道步骤 - 1].帧[帧步骤].物体变换[物体变换步骤].m[3][2] = stof(数值[11]);
            物体变换步骤++;
            break;

        case 30:
            骨骼变换步骤 = 0;
            动画轨道[轨道步骤 - 1].帧[帧步骤].骨骼变换.resize(stoi(数值[0]));
            帧步骤++;
            break;

        case 31:
            动画轨道[轨道步骤 - 1].帧[帧步骤 - 1].骨骼变换[骨骼变换步骤].m[0][0] = stof(数值[0]);
            动画轨道[轨道步骤 - 1].帧[帧步骤 - 1].骨骼变换[骨骼变换步骤].m[0][1] = stof(数值[1]);
            动画轨道[轨道步骤 - 1].帧[帧步骤 - 1].骨骼变换[骨骼变换步骤].m[0][2] = stof(数值[2]);
            动画轨道[轨道步骤 - 1].帧[帧步骤 - 1].骨骼变换[骨骼变换步骤].m[1][0] = stof(数值[3]);
            动画轨道[轨道步骤 - 1].帧[帧步骤 - 1].骨骼变换[骨骼变换步骤].m[1][1] = stof(数值[4]);
            动画轨道[轨道步骤 - 1].帧[帧步骤 - 1].骨骼变换[骨骼变换步骤].m[1][2] = stof(数值[5]);
            动画轨道[轨道步骤 - 1].帧[帧步骤 - 1].骨骼变换[骨骼变换步骤].m[2][0] = stof(数值[6]);
            动画轨道[轨道步骤 - 1].帧[帧步骤 - 1].骨骼变换[骨骼变换步骤].m[2][1] = stof(数值[7]);
            动画轨道[轨道步骤 - 1].帧[帧步骤 - 1].骨骼变换[骨骼变换步骤].m[2][2] = stof(数值[8]);
            动画轨道[轨道步骤 - 1].帧[帧步骤 - 1].骨骼变换[骨骼变换步骤].m[3][0] = stof(数值[9]);
            动画轨道[轨道步骤 - 1].帧[帧步骤 - 1].骨骼变换[骨骼变换步骤].m[3][1] = stof(数值[10]);
            动画轨道[轨道步骤 - 1].帧[帧步骤 - 1].骨骼变换[骨骼变换步骤].m[3][2] = stof(数值[11]);
            骨骼变换步骤++;
            break;

        default:
            break;
        }
    }

    输入文件.close();

    顶点单元大小 = sizeof(S顶点);
    顶点布局 = FVF位置 | FVF法向量 | FVF纹理坐标 | FVF权重 | FVF关联骨骼;

    s骨骼变换 = new XMMATRIX[骨骼数量];
    for (int i = 0; i < 骨骼数量; i++)
        s骨骼变换[i] = XMMatrixIdentity();

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
    else if (索引格式 == DXGI_FORMAT_R32_UINT)
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

    生成纹理描述符();
}

//动态物体----------------------------------------------------------------------
void C动态物体::加载FBX文件(const WCHAR* 文件路径, wstring 物体名称键, DXGI_FORMAT 索引格式, float 体素粒度)
{
    int 结果 = 1;
    UINT j = 0;
    FbxManager* lFBX管理 = NULL;
    FbxScene* l场景 = NULL;

    this->索引格式 = 索引格式;
    this->物体名称键 = 物体名称键;

    lFBX管理 = FbxManager::Create();

    FbxIOSettings* 输入 = FbxIOSettings::Create(lFBX管理, IOSROOT);
    lFBX管理->SetIOSettings(输入);
    FbxImporter* l导入 = FbxImporter::Create(lFBX管理, "");

    char* 文件名字 = 0;
    FbxWCToUTF8(文件路径, 文件名字, 0);

    if (!l导入->Initialize(文件名字, -1, 输入))
    {
        string bug = "fbx导入错误";
        bug += l导入->GetStatus().GetErrorString();
        bug += " line:";
        bug += to_string(__LINE__) + "\n";
        OutputDebugStringA(bug.c_str());
        PostQuitMessage(0);
    }

    l场景 = FbxScene::Create(lFBX管理, "myScene");

    l导入->Import(l场景);
    l导入->Destroy();

    m根节点 = new S变换节点;
    m蒙皮数据 = new S蒙皮数据;
    m动画数据 = new S动画数据;
    s备用资料 = new S备用资料;
    属性 = new C网格属性;
    FbxNode* 根节点 = l场景->GetRootNode();
    骨骼数量++;
    m骨骼名称.push_back(L"");
    m根节点->节点名称 = L"根节点";

    this->属性->纹理集.push_back(共享资源->白贴图);
    this->属性->纹理集上传.resize(1);

    if (根节点)
        for (int i = 0; i < 根节点->GetChildCount(); i++)
            加载节点(根节点->GetChild(i));
    补充骨骼树();
    骨骼数量 = m骨骼名称.size();
    加载层次(l场景);
    加载造型(l场景);

    S轴和限制 s轴和限制;
    s轴和限制.预旋转 = XMMatrixIdentity();
    轴和限制.insert(pair<wstring, S轴和限制>(L"根节点", s轴和限制));

    s骨骼变换 = new XMMATRIX[骨骼数量];
    for (int i = 0; i < 骨骼数量; i++)
        s骨骼变换[i] = XMMatrixIdentity();

    顶点单元大小 = sizeof(S顶点);

    加载动画(l场景);
    加载骨骼位置信息();
    合并物体动画信息();
    合并骨骼树(m根节点);
    优化顶点();

    s备用资料->顶点集.resize(m优化顶点集.size());
    for (int i = 0; i < m优化顶点集.size(); i++)
    {
        s备用资料->顶点集[i] = m优化顶点集[i].顶点;
    }

    if (s备用资料->顶点集.size() == 0)
    {
        wstring bug = L"无顶点 line:";
        bug += to_wstring(__LINE__) + L"\n";
        OutputDebugString(bug.c_str());
        PostQuitMessage(0);
    }

    顶点数量 = s备用资料->顶点集.size();
    顶点布局 = FVF位置 | FVF法向量 | FVF纹理坐标 | FVF权重 | FVF关联骨骼;

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

    顶点集 = new S顶点[s备用资料->顶点集.size()];
    for (int i = 0; i < s备用资料->顶点集.size(); i++)
        顶点集[i] = s备用资料->顶点集[i];

    D3D12_SUBRESOURCE_DATA subResourceData = {};
    subResourceData.pData = 顶点集;
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
        s备用资料->s索引.resize(s备用资料->索引.size());
        for (int i = 0; i < s备用资料->索引.size(); i++)
            s备用资料->s索引[i] = s备用资料->索引[i];
        subResourceData.pData = s备用资料->s索引.data();
        subResourceData.RowPitch = sizeof(USHORT) * s备用资料->s索引.size();
    }
    else if (索引格式 == DXGI_FORMAT_R32_UINT)
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

    生成纹理描述符();
    释放合并顶点索引集();
    释放合并信息();

    lFBX管理->Destroy();
}

void C动态物体::加载层次(FbxScene* p场景)
{
    int i;
    FbxNode* l根节点 = p场景->GetRootNode();
    m根节点->子节点数量 = l根节点->GetChildCount();
    if(m根节点->子节点数量)
        m根节点->子节点 = new S变换节点[l根节点->GetChildCount()];

    for (i = 0; i < l根节点->GetChildCount(); i++)
    {
        m根节点->子节点[i].父节点 = m根节点;
        加载层次(l根节点->GetChild(i), m根节点->子节点[i]);
    }
}

void C动态物体::加载层次(FbxNode* p节点, S变换节点& 节点)
{
    WCHAR* l节点名称;
    int i = 0;
    int j = 0;

    FbxUTF8ToWC(p节点->GetName(), l节点名称, 0);
    节点.节点名称 = l节点名称;
    节点.子节点数量 = p节点->GetChildCount();
    if(节点.子节点数量)
        节点.子节点 = new S变换节点[p节点->GetChildCount()];

    for (i = 0; i < m骨骼变换.size(); i++)
    {
        if (m骨骼名称[i] == l节点名称)
        {
            节点.变换.位置.y = m骨骼变换[i].SRT变换.位置.x;
            节点.变换.位置.x = -m骨骼变换[i].SRT变换.位置.y;
            节点.变换.位置.z = m骨骼变换[i].SRT变换.位置.z;
            节点.变换.旋转.x = m骨骼变换[i].SRT变换.旋转.x;
            节点.变换.旋转.y = m骨骼变换[i].SRT变换.旋转.y;
            节点.变换.旋转.z = m骨骼变换[i].SRT变换.旋转.z;
            节点.变换.缩放.x = m骨骼变换[i].SRT变换.缩放.x;
            节点.变换.缩放.y = m骨骼变换[i].SRT变换.缩放.y;
            节点.变换.缩放.z = m骨骼变换[i].SRT变换.缩放.z;
        }
    }

    for (i = 0; i < p节点->GetChildCount(); i++)
    {
        节点.子节点[i].父节点 = &节点;
        加载层次(p节点->GetChild(i), 节点.子节点[i]);
    }
}

void C动态物体::补充骨骼树()
{
    S变换节点* p变换节点 = nullptr;
    S变换节点* p变换节点2 = nullptr;

    for (int i = 0; i < m骨骼名称.size(); i++)
    {
        p变换节点 = nullptr;
        搜索骨骼树(m骨骼名称[i].c_str(), p变换节点);

        if (p变换节点)
        {
            p变换节点2 = nullptr;
            p变换节点2 = 回溯根节点(p变换节点);
            遍历骨骼树(p变换节点2);
        }
    }
}

void C动态物体::遍历骨骼树(S变换节点* p骨骼节点)
{
    bool 是否未记录 = false;

    是否未记录 = true;
    for (int j = 0; j < m骨骼名称.size(); j++)
    {
        if (m骨骼名称[j].c_str() == p骨骼节点->节点名称)
        {
            是否未记录 = false;
        }
    }
    if (是否未记录)
    {
        m骨骼名称.push_back(p骨骼节点->节点名称);
    }

    for (int i = 0; i < p骨骼节点->子节点数量; i++)
    {
        遍历骨骼树(&p骨骼节点->子节点[i]);
    }
}

C动态物体::S变换节点* C动态物体::回溯根节点(S变换节点* p骨骼节点)
{
    S变换节点* p骨骼节点2 = p骨骼节点;
    if(p骨骼节点2->父节点)
        while (p骨骼节点2->父节点->节点名称 != L"根节点")
        {
            p骨骼节点2 = p骨骼节点2->父节点;
        }

    return p骨骼节点2;
}

void C动态物体::加载节点(FbxNode* p节点)
{
    FbxNodeAttribute::EType 节点属性{};

    加载轴和限制(p节点);

    if (p节点->GetNodeAttribute())
    {
        节点属性 = p节点->GetNodeAttribute()->GetAttributeType();

        switch (节点属性)
        {
        case FbxNodeAttribute::eSkeleton:
            加载骨骼数据(p节点);
            break;

        case FbxNodeAttribute::eMesh:
            加载网格(p节点);
            加载骨骼蒙皮信息(p节点);
            break;

        default:
            break;
        }

        for (int i = 0; i < p节点->GetChildCount(); ++i)
        {
            加载节点(p节点->GetChild(i));
        }
    }
}

void C动态物体::加载轴和限制(FbxNode* p节点)
{
    S轴和限制 s轴和限制;
    FbxVector4 vec4 = p节点->GetPreRotation(FbxNode::eSourcePivot);
    //FBXSDK_printf("        Pre-Rotation: %f %f %f\n", vec4[0], vec4[1], vec4[2]);
    s轴和限制.预旋转 = XMMatrixRotationRollPitchYaw(vec4[1] * XM_PI / 180, vec4[2] * XM_PI / 180, vec4[0] * XM_PI / 180);
    WCHAR* 名称;
    FbxUTF8ToWC(p节点->GetName(), 名称, 0);
    轴和限制.insert(pair<wstring, S轴和限制>(名称, s轴和限制));
}

void C动态物体::加载网格(FbxNode* p网格节点)
{
    FbxMesh* p网格 = p网格节点->GetMesh();
    if (p网格 == NULL) return;

    XMFLOAT3 l位置[3]{};
    XMFLOAT3 l法向量[3]{};
    XMFLOAT3 l切向量[3]{};
    XMFLOAT2 l纹理坐标[4]{};
    UINT i = 0;
    UINT j = 0;
    UINT k = 0;
    UINT l = 0;
    UINT m = 0;
    UINT l多边形数量 = p网格->GetPolygonCount();
    UINT l当前顶点计数 = 0;
    UINT l多边形顶点数量 = 0;
    UINT l当前索引数量 = 0;
    UINT l骨骼索引计数 = 0;

    for (i = 0; i < l多边形数量; i++)
    {
        int 当前多边形顶点数量 = p网格->GetPolygonSize(i);
        索引数量 += (当前多边形顶点数量 - 2) * 3;
        l当前索引数量 += (当前多边形顶点数量 - 2) * 3;
    }

    s备用资料->索引.resize(索引数量);
    UINT 控制顶点数量 = p网格->GetControlPointsCount();

    WCHAR* 物体名称;
    FbxUTF8ToWC(p网格节点->GetName(), 物体名称);

    m物体控制顶点集.resize(m物体控制顶点集.size() + 1);
    m物体控制顶点集[m物体控制顶点集.size() - 1].物体名称 = 物体名称;
    m物体控制顶点集[m物体控制顶点集.size() - 1].控制顶点集.resize(控制顶点数量);

    XMMATRIX 旋转修正 = XMMatrixIdentity();
    //旋转修正 *= XMMatrixRotationAxis(XMVECTOR{ 0.0f, 1.0f, 0.0f, 0.0f }, XM_PI / 2);
    //旋转修正 *= XMMatrixRotationAxis(XMVECTOR{ 0.0f, 0.0f, 1.0f, 0.0f }, XM_PI / 2);

    for (i = 0; i < l多边形数量; i++)
    {
        l多边形顶点数量 = p网格->GetPolygonSize(i);
        for (j = 0; j < l多边形顶点数量; j++)
        {
            int l控制顶点索引 = p网格->GetPolygonVertex(i, j);
            int id;
            FbxVector4* 控制顶点 = p网格->GetControlPoints();
            S顶点 顶点;
            XMVECTOR 顶点变换 = { 0.0f, 0.0f, 0.0f, 0.0f };
            顶点变换.m128_f32[0] = 控制顶点[l控制顶点索引].mData[1];
            顶点变换.m128_f32[1] = 控制顶点[l控制顶点索引].mData[2];
            顶点变换.m128_f32[2] = 控制顶点[l控制顶点索引].mData[0];
            顶点变换 = XMVector3TransformCoord(顶点变换, 旋转修正);

            顶点.位置.x = 顶点变换.m128_f32[0];
            顶点.位置.y = 顶点变换.m128_f32[1];
            顶点.位置.z = 顶点变换.m128_f32[2];

            FbxGeometryElementUV* p纹理坐标 = p网格->GetElementUV(0);

            if (p纹理坐标)
                switch (p纹理坐标->GetMappingMode())
                {
                case FbxGeometryElement::eByControlPoint:
                    switch (p纹理坐标->GetReferenceMode())
                    {
                    case FbxGeometryElement::eDirect:
                        顶点.纹理坐标.x = p纹理坐标->GetDirectArray().GetAt(l控制顶点索引).mData[0];
                        顶点.纹理坐标.y = 1.0f - p纹理坐标->GetDirectArray().GetAt(l控制顶点索引).mData[1];
                        break;

                    case FbxGeometryElement::eIndexToDirect:
                        id = p纹理坐标->GetIndexArray().GetAt(l控制顶点索引);
                        顶点.纹理坐标.x = p纹理坐标->GetDirectArray().GetAt(id).mData[0];
                        顶点.纹理坐标.y = 1.0f - p纹理坐标->GetDirectArray().GetAt(id).mData[1];
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
                        顶点.纹理坐标.x = p纹理坐标->GetDirectArray().GetAt(p网格->GetTextureUVIndex(i, j)).mData[0];
                        顶点.纹理坐标.y = 1.0f - p纹理坐标->GetDirectArray().GetAt(p网格->GetTextureUVIndex(i, j)).mData[1];
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
                    顶点变换.m128_f32[0] = p法向量->GetDirectArray().GetAt(l控制顶点索引).mData[1];
                    顶点变换.m128_f32[1] = p法向量->GetDirectArray().GetAt(l控制顶点索引).mData[2];
                    顶点变换.m128_f32[2] = p法向量->GetDirectArray().GetAt(l控制顶点索引).mData[0];
                    顶点变换 = XMVector3Transform(顶点变换, 旋转修正);
                    顶点.法向量.x = 顶点变换.m128_f32[0];
                    顶点.法向量.y = 顶点变换.m128_f32[1];
                    顶点.法向量.z = 顶点变换.m128_f32[2];
                    break;

                case FbxGeometryElement::eIndexToDirect:
                    id = p法向量->GetIndexArray().GetAt(l控制顶点索引);
                    顶点变换.m128_f32[0] = p法向量->GetDirectArray().GetAt(id).mData[1];
                    顶点变换.m128_f32[1] = p法向量->GetDirectArray().GetAt(id).mData[2];
                    顶点变换.m128_f32[2] = p法向量->GetDirectArray().GetAt(id).mData[0];
                    顶点变换 = XMVector3Transform(顶点变换, 旋转修正);
                    顶点.法向量.x = 顶点变换.m128_f32[0];
                    顶点.法向量.y = 顶点变换.m128_f32[1];
                    顶点.法向量.z = 顶点变换.m128_f32[2];
                    break;

                default:
                    break;
                }
                break;

            case FbxGeometryElement::eByPolygonVertex:
                switch (p法向量->GetReferenceMode())
                {
                case FbxGeometryElement::eDirect:
                    顶点变换.m128_f32[0] = p法向量->GetDirectArray().GetAt(l当前顶点计数).mData[1];
                    顶点变换.m128_f32[1] = p法向量->GetDirectArray().GetAt(l当前顶点计数).mData[2];
                    顶点变换.m128_f32[2] = p法向量->GetDirectArray().GetAt(l当前顶点计数).mData[0];
                    顶点变换 = XMVector3Transform(顶点变换, 旋转修正);
                    顶点.法向量.x = 顶点变换.m128_f32[0];
                    顶点.法向量.y = 顶点变换.m128_f32[1];
                    顶点.法向量.z = 顶点变换.m128_f32[2];
                    break;

                case FbxGeometryElement::eIndexToDirect:
                    id = p法向量->GetIndexArray().GetAt(l当前顶点计数);
                    顶点变换.m128_f32[0] = p法向量->GetDirectArray().GetAt(id).mData[1];
                    顶点变换.m128_f32[1] = p法向量->GetDirectArray().GetAt(id).mData[2];
                    顶点变换.m128_f32[2] = p法向量->GetDirectArray().GetAt(id).mData[0];
                    顶点变换 = XMVector3Transform(顶点变换, 旋转修正);
                    顶点.法向量.x = 顶点变换.m128_f32[0];
                    顶点.法向量.y = 顶点变换.m128_f32[1];
                    顶点.法向量.z = 顶点变换.m128_f32[2];
                    break;

                default:
                    break;
                }
                break;
            }

            添加顶点(l控制顶点索引, &顶点, m顶点计数);
            m顶点计数++;
            l当前顶点计数++;
        }

        for (k = 0; k < l多边形顶点数量 - 2; k++)
        {
            s备用资料->索引[m索引计数] = m顶点计数 - l多边形顶点数量;
            m索引计数++;
            s备用资料->索引[m索引计数] = m顶点计数 - k - 1;
            m索引计数++;
            s备用资料->索引[m索引计数] = m顶点计数 - k - 2;
            m索引计数++;
        }
    }


    C网格属性::S属性* 属性 = new C网格属性::S属性;

    WCHAR* 网格名称 = 0;
    FbxUTF8ToWC(p网格节点->GetName(), 网格名称, 0);
    属性->物体名称 = 网格名称;

    加载材质(p网格节点, 属性);

    XMMATRIX 旋转修正2 = XMMatrixIdentity();
    旋转修正2 *= XMMatrixRotationAxis(XMVECTOR{ 0.0f, 0.0f, 1.0f, 0.0f }, XM_PI / 2);
    XMMATRIX 旋转修正3 = XMMatrixRotationAxis(XMVECTOR{ 0.0f, 1.0f, 0.0f, 0.0f }, -XM_PI / 2);

    属性->索引数量 = l当前索引数量;
    属性->起始索引 = m索引计数 - l当前索引数量;
    XMMATRIX 缩放矩阵 = XMMatrixIdentity();
    XMMATRIX 旋转矩阵 = XMMatrixIdentity();
    XMMATRIX 位移矩阵 = XMMatrixIdentity();
    缩放矩阵 = XMMatrixScaling(p网格节点->LclScaling.Get().mData[0], p网格节点->LclScaling.Get().mData[1],
        p网格节点->LclScaling.Get().mData[2]);
    float x = p网格节点->LclRotation.Get().mData[1];    float y = p网格节点->LclRotation.Get().mData[2];    float z = p网格节点->LclRotation.Get().mData[0];
    旋转矩阵 *= XMMatrixRotationRollPitchYaw(p网格节点->LclRotation.Get().mData[1] * XM_PI / 180,
        p网格节点->LclRotation.Get().mData[2] * XM_PI / 180, p网格节点->LclRotation.Get().mData[0] * XM_PI / 180);
    旋转矩阵 = 轴和限制[网格名称].预旋转 * 旋转修正2 * 旋转矩阵;
    位移矩阵 *= XMMatrixTranslation(p网格节点->LclTranslation.Get().mData[0], p网格节点->LclTranslation.Get().mData[1],
        p网格节点->LclTranslation.Get().mData[2]);
    位移矩阵 = 位移矩阵 * 旋转修正3;
    位移矩阵.r[0].m128_f32[0] = 1.0f; 位移矩阵.r[0].m128_f32[1] = 0.0f; 位移矩阵.r[0].m128_f32[2] = 0.0f;
    位移矩阵.r[1].m128_f32[0] = 0.0f; 位移矩阵.r[1].m128_f32[1] = 1.0f; 位移矩阵.r[1].m128_f32[2] = 0.0f;
    位移矩阵.r[2].m128_f32[0] = 0.0f; 位移矩阵.r[2].m128_f32[1] = 0.0f; 位移矩阵.r[2].m128_f32[2] = 1.0f;
    属性->变换 = 缩放矩阵 * 旋转矩阵 * 位移矩阵;

    this->属性->添加元素(属性);
}

void C动态物体::加载材质(FbxNode* p网格节点, C网格属性::S属性* 属性)
{
    FbxMesh* p网格 = p网格节点->GetMesh();
    int 材质数量 = 0;

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
        属性->材质.光泽度 = 0.0f;
        属性->材质.不透明度 = 1.0f;
        属性->材质.高光级别 = 1.0f;
        属性->纹理索引 = 0;
    }
}

void C动态物体::加载材质属性(FbxSurfaceMaterial* p表面材质, C网格属性::S属性* 属性)
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

    加载纹理(p表面材质, 属性);
}

void C动态物体::加载纹理(FbxSurfaceMaterial* p表面材质, C网格属性::S属性* 属性)
{
    int i;
    int k = 0;
    int 结果 = 1;
    FbxProperty 材质属性;
    WCHAR* 路径 = 0;

    for (i = 0; i < FbxLayerElement::sTypeTextureCount; i++)
    {
        材质属性 = p表面材质->FindProperty(FbxLayerElement::sTextureChannelNames[i]);
        if (材质属性.IsValid())
        {
            int textureCount = 材质属性.GetSrcObjectCount();

            for (int j = 0; j < textureCount; ++j)
            {
                FbxFileTexture* p纹理 = FbxCast<FbxFileTexture>(材质属性.GetSrcObject(j));
                if (p纹理)
                {
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

                        this->属性->纹理集.resize(this->属性->纹理集.size() + 1);
                        this->属性->纹理集上传.resize(this->属性->纹理集上传.size() + 1);
                        if (文件类型 == L"dds")
                        {
                            if (!SUCCEEDED(CreateDDSTextureFromFile12(设备.Get(), 命令队列.Get(), 路径, this->属性->纹理集[this->属性->纹理集.size() - 1],
                                this->属性->纹理集上传[this->属性->纹理集上传.size() - 1])))
                            {
                                wstring bug = L"加载模型材质时未找到贴图文件 line:";
                                bug += to_wstring(__LINE__) + L"\n";
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

void C动态物体::生成纹理描述符()
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

void C动态物体::合并顶点(UINT 控制顶点集, UINT 控制顶点索引, float 最小cos角度, float 最大uv间隔)
{;
    UINT 顶点数量 = 0;
    UINT 当前顶点 = 0;
    S优化顶点集* 顶点集;
    UINT i = 0;
    UINT j = 0;
    UINT k = 0;
    UINT l = 0;
    UINT m = 0;
    UINT n = 0;
    UINT u = 0;
    float 权重和 = 0;
    UINT 骨骼索引计数 = 0;
    UINT 最小骨骼索引;
    float 最小权重 = 1.0f;
    bool l跳出 = 0;

    顶点数量 = m物体控制顶点集[控制顶点集].控制顶点集[控制顶点索引].size();

    顶点集 = new S优化顶点集[顶点数量];

    //合并骨骼信息
    for(m = 0; m < 顶点数量; m++)
    {
        骨骼索引计数 = 0;
        for (i = 0; i < m蒙皮数据->关联物体.size(); i++)
        {
            if(m蒙皮数据->关联物体[i].物体名称 == m物体控制顶点集[控制顶点集].物体名称)
            for (k = 0; k < m蒙皮数据->关联物体[i].骨骼.size(); k++)
            {
                for (l = 0; l < m蒙皮数据->关联物体[i].骨骼[k].索引组.size(); l++)
                {
                    if (m蒙皮数据->关联物体[i].骨骼[k].索引组[l] == 控制顶点索引)
                    {
                        for (j = 0; j < 骨骼数量; j++)
                        {
                            if (m蒙皮数据->关联物体[i].骨骼[k].骨骼名称 == m骨骼名称[j])
                            {
                                if (m蒙皮数据->关联物体[i].骨骼[k].权重组[l] > 0.001)
                                {
                                    //丢弃最小权重骨骼
                                    if (骨骼索引计数 == d最大骨骼索引数量)
                                    {
                                        最小权重 = 1.0f;
                                        for (n = 0; n < d最大骨骼索引数量 - 1; n++)
                                        {
                                            if (最小权重 > m物体控制顶点集[控制顶点集].控制顶点集[控制顶点索引][m].顶点.索引权重[n])
                                            {
                                                最小骨骼索引 = n;
                                                最小权重 = m物体控制顶点集[控制顶点集].控制顶点集[控制顶点索引][m].顶点.索引权重[n];
                                            }
                                        }

                                        if (最小权重 < m蒙皮数据->关联物体[i].骨骼[k].权重组[l])
                                        {
                                            m物体控制顶点集[控制顶点集].控制顶点集[控制顶点索引][m].顶点.索引权重[最小骨骼索引] = 
                                                m蒙皮数据->关联物体[i].骨骼[k].权重组[l] + 最小权重;
                                            m物体控制顶点集[控制顶点集].控制顶点集[控制顶点索引][m].顶点.关联骨骼索引[最小骨骼索引] = j;
                                        }

                                        continue;
                                    }

                                    m物体控制顶点集[控制顶点集].控制顶点集[控制顶点索引][m].顶点.关联骨骼索引[骨骼索引计数] = j;
                                    if(骨骼索引计数 < 3)
                                        m物体控制顶点集[控制顶点集].控制顶点集[控制顶点索引][m].顶点.索引权重[骨骼索引计数] = 
                                            m蒙皮数据->关联物体[i].骨骼[k].权重组[l];
                                    骨骼索引计数++;
                                }
                            }
                        }
                    }
                }
            }
        }

        for (k = 骨骼索引计数; k < d最大骨骼索引数量; k++)
        {
            m物体控制顶点集[控制顶点集].控制顶点集[控制顶点索引][m].顶点.关联骨骼索引[k] = 0;
            if (k < d最大骨骼索引数量 - 1) m物体控制顶点集[控制顶点集].控制顶点集[控制顶点索引][m].顶点.索引权重[k] = 0;
        }

        顶点集[当前顶点].顶点 = m物体控制顶点集[控制顶点集].控制顶点集[控制顶点索引][m].顶点;
        顶点集[当前顶点].索引 = m物体控制顶点集[控制顶点集].控制顶点集[控制顶点索引][m].索引;
        当前顶点++;
    }

    XMVECTOR 法向量1, 法向量2;
    XMVECTOR 纹理1, 纹理2;

    for (i = 0; i < 顶点数量; i++)
    {
        for (j = i + 1; j < 顶点数量; j++)
        {
            法向量1 = XMLoadFloat3(&顶点集[i].顶点.法向量);
            法向量2 = XMLoadFloat3(&顶点集[j].顶点.法向量);
            纹理1 = XMLoadFloat2(&顶点集[i].顶点.纹理坐标);
            纹理2 = XMLoadFloat2(&顶点集[j].顶点.纹理坐标);

            if (XMVector3Dot(法向量1, 法向量2).m128_f32[0] < 最小cos角度 ||
                XMVector2Length(纹理1 - 纹理2).m128_f32[0] > 最大uv间隔)
            {
                for (k = 0; k < 顶点数量; k++)
                {
                    m优化顶点集.resize(m优化顶点集.size() + 1);
                    m优化顶点集[m优化顶点集.size() - 1].顶点 = 顶点集[k].顶点;
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
    m合并索引集[m合并索引集.size() - 1].副索引集.resize(顶点数量);

    法向量1 = { 0.0f, 0.0f, 0.0f, 0.0f };
    for (i = 0; i < 顶点数量; i++)
    {
        m合并索引集[m合并索引集.size() - 1].副索引集[i] = 顶点集[i].索引;
        法向量1 += XMLoadFloat3(&顶点集[i].顶点.法向量);
    }
    法向量1 = 法向量1 / 顶点数量;

    m优化顶点集.resize(m优化顶点集.size() + 1);
    m优化顶点集[m优化顶点集.size() - 1].顶点 = 顶点集[0].顶点;
    XMStoreFloat3(&m优化顶点集[m优化顶点集.size() - 1].顶点.法向量, 法向量1);
    m优化顶点集[m优化顶点集.size() - 1].索引 = 顶点集[0].索引;

跳出:
    delete[] 顶点集; 顶点集 = nullptr;
}

void C动态物体::添加顶点(UINT 控制顶点索引, S顶点* 顶点, UINT 索引)
{
    UINT i = 0;

    i = m物体控制顶点集[m物体控制顶点集.size() - 1].控制顶点集[控制顶点索引].size();
    m物体控制顶点集[m物体控制顶点集.size() - 1].控制顶点集[控制顶点索引].resize(i + 1);

    m物体控制顶点集[m物体控制顶点集.size() - 1].控制顶点集[控制顶点索引][i].顶点 = *顶点;
    m物体控制顶点集[m物体控制顶点集.size() - 1].控制顶点集[控制顶点索引][i].索引 = 索引;
}

void C动态物体::优化顶点()
{
    float 最小cos角度 = cosf(法向量合并最大角度);
    UINT i = 0;
    UINT j = 0;
    UINT k = 0;

    for (i = 0; i < m物体控制顶点集.size(); i++)
        for (j = 0; j < m物体控制顶点集[i].控制顶点集.size(); j++)
            合并顶点(i, j, 最小cos角度, 贴图顶点采样最大间隔);

    thread* 线程 = new thread[线程数量];
    bool* 是否结束 = new bool[线程数量];

    for (int i = 0; i < 线程数量; i++)
    {
        是否结束[i] = true;
        线程[i] = thread(优化顶点线程初始化);
    }

    bool 是否继续 = true;

    for (i = 0; i < 索引数量; i++)
    {
        while (1)
        {
            for (int j = 0; j < 线程数量; j++)
            {
                if (是否结束[j] == true)
                {
                    线程[j].join();
                    是否结束[j] = false;

                    线程[j] = thread(优化顶点线程, s备用资料, &m合并索引集, i, &是否结束[j]);

                    goto 结束线程;
                }
            }
        }

    结束线程: continue;
    }

    for (int i = 0; i < 线程数量; i++)
        线程[i].join();

    delete[] 线程;
    delete[] 是否结束;
}

void C动态物体::优化顶点线程(S备用资料* s备用资料, vector<S合并索引集>* m合并索引集, int i, bool* 是否结束)
{
    int j = 0;
    int k = 0;

    for (j = 0; j < (*m合并索引集).size(); j++)
    {
        for (k = 0; k < (*m合并索引集)[j].副索引集.size(); k++)
        {
            if (s备用资料->索引[i] == (*m合并索引集)[j].副索引集[k])
            {
                s备用资料->索引[i] = (*m合并索引集)[j].主索引;
                *是否结束 = 1;
                return;
            }
        }
    }

    *是否结束 = true;
}

void C动态物体::优化顶点线程初始化()
{

}

void C动态物体::加载动画(FbxScene* p场景)
{
    m动画数据->片段.resize(p场景->GetSrcObjectCount<FbxAnimStack>());

    char lTimeString[256]{};

    FbxTime   l帧时间;
    FbxTimeSpan l时间跨度;
    FbxTime     l开始, l结束;
    FbxGlobalSettings* p设定 = 0;
    int l帧速率 = 0;
    int l时 = 0;
    int l分 = 0;
    int l秒 = 0;
    int l帧 = 0;
    int l域 = 0;
    int l残值 = 0;

    l帧速率 = l帧时间.GetFrameRate(l帧时间.eDefaultMode);
    m动画数据->帧速率 = l帧速率;

    p设定 = &p场景->GetGlobalSettings();

    p设定->GetTimelineDefaultTimeSpan(l时间跨度);
    l开始 = l时间跨度.GetStart();
    l结束 = l时间跨度.GetStop();
    l开始.GetTime(l时, l分, l秒, l帧, l域, l残值);
    m动画数据->开始帧 = l时 * l帧速率 * l帧速率 * l帧速率 + l分 * l帧速率 * l帧速率 + l秒 * l帧速率 + l帧;
    l结束.GetTime(l时, l分, l秒, l帧, l域, l残值);
    m动画数据->结束帧 = l时 * l帧速率 * l帧速率 * l帧速率 + l分 * l帧速率 * l帧速率 + l秒 * l帧速率 + l帧;

    for (UINT i = 0; i < p场景->GetSrcObjectCount<FbxAnimStack>(); i++)
    {
        FbxAnimStack* l动画片段 = p场景->GetSrcObject<FbxAnimStack>(i);

        WCHAR* 片段名称 = 0;
        FbxUTF8ToWC(l动画片段->GetName(),片段名称, 0);
        m动画数据->片段[i].片段名称 = 片段名称;

        加载动画片段(l动画片段, p场景->GetRootNode(), i);
    }
}

void C动态物体::加载动画片段(FbxAnimStack* p动画片段, FbxNode* p节点, UINT 片段索引)
{
    int l;
    int 动画层数量 = p动画片段->GetMemberCount<FbxAnimLayer>();
    int 音效层数量 = p动画片段->GetMemberCount<FbxAudioLayer>();
    FbxTimeSpan 时间跨度;
    FbxTime l帧时间;
    FbxTime l开始, l结束;
    int l帧速率 = 0;
    int l时 = 0;
    int l分 = 0;
    int l秒 = 0;
    int l帧 = 0;
    int l域 = 0;
    int l残值 = 0;

    if (动画层数量)
        m动画数据->片段[片段索引].动画层.resize(动画层数量);

    if (音效层数量)
        m动画数据->片段[片段索引].音效层.resize(音效层数量);

    时间跨度 = p动画片段->GetLocalTimeSpan();
    l帧速率 = l帧时间.GetFrameRate(l帧时间.eDefaultMode);

    l开始 = 时间跨度.GetStart();
    l结束 = 时间跨度.GetStop();
    l开始.GetTime(l时, l分, l秒, l帧, l域, l残值);
    m动画数据->片段[片段索引].开始帧 = l时 * l帧速率 * l帧速率 * l帧速率 + l分 * l帧速率 * l帧速率 + l秒 * l帧速率 + l帧;
    l结束.GetTime(l时, l分, l秒, l帧, l域, l残值);
    m动画数据->片段[片段索引].结束帧 = l时 * l帧速率 * l帧速率 * l帧速率 + l分 * l帧速率 * l帧速率 + l秒 * l帧速率 + l帧;
    m动画数据->片段[片段索引].帧速率 = l帧速率;

    for (l = 0; l < 动画层数量; l++)
    {
        FbxAnimLayer* l动画层 = p动画片段->GetMember<FbxAnimLayer>(l);

        WCHAR* 动画层名称 = 0;
        FbxUTF8ToWC(l动画层->GetName(), 动画层名称);
        m动画数据->片段[片段索引].动画层[l].动画层名称, 动画层名称 = 动画层名称;

        加载动画层(l动画层, p节点, 片段索引, l);
    }

    for (l = 0; l < 音效层数量; l++)
    {
        FbxAudioLayer* l音效层 = p动画片段->GetMember<FbxAudioLayer>(l);
        加载音效层(l音效层, l, 片段索引);
    }
}

void C动态物体::加载音效层(FbxAudioLayer* p音效层, UINT 音效层索引, UINT 片段索引)
{
    int l音轨数量;
    WCHAR* l音效层名称 = 0;
    WCHAR* l音轨名称 = 0;

    l音轨数量 = p音效层->GetMemberCount<FbxAudio>();

    m动画数据->片段[片段索引].音效层[音效层索引].音轨.resize(l音轨数量);

    FbxUTF8ToWC(p音效层->GetName(), l音效层名称);
    m动画数据->片段[片段索引].音效层[音效层索引].音效层名称 = l音效层名称;

    for (int i = 0; i < l音轨数量; i++)
    {
        FbxAudio* l音轨 = p音效层->GetMember<FbxAudio>(i);
        FbxUTF8ToWC(l音轨->GetName(), l音轨名称, 0);
        m动画数据->片段[片段索引].音效层[音效层索引].音轨[i].音轨名称 = l音轨名称;
    }
}

void C动态物体::加载动画层(FbxAnimLayer* p动画层, FbxNode* p节点, UINT 片段索引, UINT 动画层索引)
{
    int l模型数量;
    WCHAR* l物体名称;

    for (l模型数量 = 0; l模型数量 < p节点->GetChildCount(); l模型数量++)
    {
        加载动画层(p动画层, p节点->GetChild(l模型数量), 片段索引, 动画层索引);
    }

    FbxUTF8ToWC(p节点->GetName(), l物体名称, 0);
    m动画数据->片段[片段索引].动画层[动画层索引].物体.resize(m动画数据->片段[片段索引].动画层[动画层索引].物体.size() + 1);
    m动画数据->片段[片段索引].动画层[动画层索引].物体[m动画数据->片段[片段索引].动画层[动画层索引].物体.size() - 1].物体名称 = l物体名称;

    加载动画通道(p动画层, p节点, 片段索引, 动画层索引, m动画数据->片段[片段索引].动画层[动画层索引].物体.size() - 1);
}

void C动态物体::加载动画通道(FbxAnimLayer* p动画层, FbxNode* p节点, UINT 片段索引, UINT 动画层索引, UINT 模型索引)
{
    FbxAnimCurve* l动画曲线 = NULL;

    FbxTime   l帧时间;
    float   l帧值;
    int     l帧计数;
    int l帧速率;

    int l时;
    int l分;
    int l秒;
    int l帧;
    int l域;
    int l残值;
    int l倍数 = 0;
    int l余数 = 0;

    //显示一般曲线。
    l动画曲线 = p节点->LclTranslation.GetCurve(p动画层, FBXSDK_CURVENODE_COMPONENT_X);
    if (l动画曲线)
    {
        int l帧数量 = l动画曲线->KeyGetCount();
        if (l帧数量 > m动画数据->片段[片段索引].动画层[动画层索引].物体[模型索引].位置.size())
            m动画数据->片段[片段索引].动画层[动画层索引].物体[模型索引].位置.resize(l帧数量);

        for (l帧计数 = 0; l帧计数 < l帧数量; l帧计数++)
        {
            l帧值 = (float)l动画曲线->KeyGetValue(l帧计数);
            l帧时间 = l动画曲线->KeyGetTime(l帧计数);
            l帧时间.GetTime(l时, l分, l秒, l帧, l域, l残值);
            l帧速率 = l帧时间.GetFrameRate(l帧时间.eDefaultMode);

            m动画数据->片段[片段索引].动画层[动画层索引].物体[模型索引].位置[l帧计数].帧数 =
                l时 * l帧速率 * l帧速率 * l帧速率 + l分 * l帧速率 * l帧速率 + l秒 * l帧速率 + l帧;
            m动画数据->片段[片段索引].动画层[动画层索引].物体[模型索引].位置[l帧计数].位置.x = l帧值;
        }
    }
    l动画曲线 = p节点->LclTranslation.GetCurve(p动画层, FBXSDK_CURVENODE_COMPONENT_Y);
    if (l动画曲线)
    {
        int l帧数量 = l动画曲线->KeyGetCount();
        if (l帧数量 > m动画数据->片段[片段索引].动画层[动画层索引].物体[模型索引].位置.size())
            m动画数据->片段[片段索引].动画层[动画层索引].物体[模型索引].位置.resize(l帧数量);

        for (l帧计数 = 0; l帧计数 < l帧数量; l帧计数++)
        {
            l帧值 = (float)l动画曲线->KeyGetValue(l帧计数);
            l帧时间 = l动画曲线->KeyGetTime(l帧计数);
            l帧时间.GetTime(l时, l分, l秒, l帧, l域, l残值);
            l帧速率 = l帧时间.GetFrameRate(l帧时间.eDefaultMode);

            m动画数据->片段[片段索引].动画层[动画层索引].物体[模型索引].位置[l帧计数].帧数 =
                l时 * l帧速率 * l帧速率 * l帧速率 + l分 * l帧速率 * l帧速率 + l秒 * l帧速率 + l帧;
            m动画数据->片段[片段索引].动画层[动画层索引].物体[模型索引].位置[l帧计数].位置.y = l帧值;
        }
    }
    l动画曲线 = p节点->LclTranslation.GetCurve(p动画层, FBXSDK_CURVENODE_COMPONENT_Z);
    if (l动画曲线)
    {
        int l帧数量 = l动画曲线->KeyGetCount();
        if (l帧数量 > m动画数据->片段[片段索引].动画层[动画层索引].物体[模型索引].位置.size())
            m动画数据->片段[片段索引].动画层[动画层索引].物体[模型索引].位置.resize(l帧数量);

        for (l帧计数 = 0; l帧计数 < l帧数量; l帧计数++)
        {
            l帧值 = (float)l动画曲线->KeyGetValue(l帧计数);
            l帧时间 = l动画曲线->KeyGetTime(l帧计数);
            l帧时间.GetTime(l时, l分, l秒, l帧, l域, l残值);
            l帧速率 = l帧时间.GetFrameRate(l帧时间.eDefaultMode);

            m动画数据->片段[片段索引].动画层[动画层索引].物体[模型索引].位置[l帧计数].帧数 =
                l时 * l帧速率 * l帧速率 * l帧速率 + l分 * l帧速率 * l帧速率 + l秒 * l帧速率 + l帧;
            m动画数据->片段[片段索引].动画层[动画层索引].物体[模型索引].位置[l帧计数].位置.z = l帧值;
        }
    }

    l动画曲线 = p节点->LclRotation.GetCurve(p动画层, FBXSDK_CURVENODE_COMPONENT_X);
    if (l动画曲线)
    {
        int l帧数量 = l动画曲线->KeyGetCount();
        if (l帧数量 > m动画数据->片段[片段索引].动画层[动画层索引].物体[模型索引].旋转.size())
            m动画数据->片段[片段索引].动画层[动画层索引].物体[模型索引].旋转.resize(l帧数量);

        for (l帧计数 = 0; l帧计数 < l帧数量; l帧计数++)
        {
            l帧值 = (float)l动画曲线->KeyGetValue(l帧计数);
            l帧时间 = l动画曲线->KeyGetTime(l帧计数);
            l帧时间.GetTime(l时, l分, l秒, l帧, l域, l残值);
            l帧速率 = l帧时间.GetFrameRate(l帧时间.eDefaultMode);

            m动画数据->片段[片段索引].动画层[动画层索引].物体[模型索引].旋转[l帧计数].帧数 =
                l时 * l帧速率 * l帧速率 * l帧速率 + l分 * l帧速率 * l帧速率 + l秒 * l帧速率 + l帧;
            m动画数据->片段[片段索引].动画层[动画层索引].物体[模型索引].旋转[l帧计数].旋转.x = l帧值;
        }
    }
    l动画曲线 = p节点->LclRotation.GetCurve(p动画层, FBXSDK_CURVENODE_COMPONENT_Y);
    if (l动画曲线)
    {
        int l帧数量 = l动画曲线->KeyGetCount();
        if(l帧数量 > m动画数据->片段[片段索引].动画层[动画层索引].物体[模型索引].旋转.size())
            m动画数据->片段[片段索引].动画层[动画层索引].物体[模型索引].旋转.resize(l帧数量);

        for (l帧计数 = 0; l帧计数 < l帧数量; l帧计数++)
        {
            l帧值 = (float)l动画曲线->KeyGetValue(l帧计数);
            l帧时间 = l动画曲线->KeyGetTime(l帧计数);
            l帧时间.GetTime(l时, l分, l秒, l帧, l域, l残值);
            l帧速率 = l帧时间.GetFrameRate(l帧时间.eDefaultMode);

            m动画数据->片段[片段索引].动画层[动画层索引].物体[模型索引].旋转[l帧计数].帧数 =
                l时 * l帧速率 * l帧速率 * l帧速率 + l分 * l帧速率 * l帧速率 + l秒 * l帧速率 + l帧;
            m动画数据->片段[片段索引].动画层[动画层索引].物体[模型索引].旋转[l帧计数].旋转.y = l帧值;
        }
    }
    l动画曲线 = p节点->LclRotation.GetCurve(p动画层, FBXSDK_CURVENODE_COMPONENT_Z);
    if (l动画曲线)
    {
        int l帧数量 = l动画曲线->KeyGetCount();
        if (l帧数量 > m动画数据->片段[片段索引].动画层[动画层索引].物体[模型索引].旋转.size())
            m动画数据->片段[片段索引].动画层[动画层索引].物体[模型索引].旋转.resize(l帧数量);

        for (l帧计数 = 0; l帧计数 < l帧数量; l帧计数++)
        {
            l帧值 = (float)l动画曲线->KeyGetValue(l帧计数);
            l帧时间 = l动画曲线->KeyGetTime(l帧计数);
            l帧时间.GetTime(l时, l分, l秒, l帧, l域, l残值);
            l帧速率 = l帧时间.GetFrameRate(l帧时间.eDefaultMode);

            m动画数据->片段[片段索引].动画层[动画层索引].物体[模型索引].旋转[l帧计数].帧数 =
                l时 * l帧速率 * l帧速率 * l帧速率 + l分 * l帧速率 * l帧速率 + l秒 * l帧速率 + l帧;
            m动画数据->片段[片段索引].动画层[动画层索引].物体[模型索引].旋转[l帧计数].旋转.z = l帧值;
        }
    }

    l动画曲线 = p节点->LclScaling.GetCurve(p动画层, FBXSDK_CURVENODE_COMPONENT_X);
    if (l动画曲线)
    {
        int l帧数量 = l动画曲线->KeyGetCount();
        if (l帧数量 > m动画数据->片段[片段索引].动画层[动画层索引].物体[模型索引].缩放.size())
            m动画数据->片段[片段索引].动画层[动画层索引].物体[模型索引].缩放.resize(l帧数量);

        for (l帧计数 = 0; l帧计数 < l帧数量; l帧计数++)
        {
            l帧值 = (float)l动画曲线->KeyGetValue(l帧计数);
            l帧时间 = l动画曲线->KeyGetTime(l帧计数);
            l帧时间.GetTime(l时, l分, l秒, l帧, l域, l残值);
            l帧速率 = l帧时间.GetFrameRate(l帧时间.eDefaultMode);

            m动画数据->片段[片段索引].动画层[动画层索引].物体[模型索引].缩放[l帧计数].帧数 =
                l时 * l帧速率 * l帧速率 * l帧速率 + l分 * l帧速率 * l帧速率 + l秒 * l帧速率 + l帧;
            m动画数据->片段[片段索引].动画层[动画层索引].物体[模型索引].缩放[l帧计数].缩放.x = l帧值;
        }
    }
    l动画曲线 = p节点->LclScaling.GetCurve(p动画层, FBXSDK_CURVENODE_COMPONENT_Y);
    if (l动画曲线)
    {
        int l帧数量 = l动画曲线->KeyGetCount();
        if (l帧数量 > m动画数据->片段[片段索引].动画层[动画层索引].物体[模型索引].缩放.size())
            m动画数据->片段[片段索引].动画层[动画层索引].物体[模型索引].缩放.resize(l帧数量);

        for (l帧计数 = 0; l帧计数 < l帧数量; l帧计数++)
        {
            l帧值 = (float)l动画曲线->KeyGetValue(l帧计数);
            l帧时间 = l动画曲线->KeyGetTime(l帧计数);
            l帧时间.GetTime(l时, l分, l秒, l帧, l域, l残值);
            l帧速率 = l帧时间.GetFrameRate(l帧时间.eDefaultMode);

            m动画数据->片段[片段索引].动画层[动画层索引].物体[模型索引].缩放[l帧计数].帧数 =
                l时 * l帧速率 * l帧速率 * l帧速率 + l分 * l帧速率 * l帧速率 + l秒 * l帧速率 + l帧;
            m动画数据->片段[片段索引].动画层[动画层索引].物体[模型索引].缩放[l帧计数].缩放.y = l帧值;
        }
    }
    l动画曲线 = p节点->LclScaling.GetCurve(p动画层, FBXSDK_CURVENODE_COMPONENT_Z);
    if (l动画曲线)
    {
        int l帧数量 = l动画曲线->KeyGetCount();
        if (l帧数量 > m动画数据->片段[片段索引].动画层[动画层索引].物体[模型索引].缩放.size())
            m动画数据->片段[片段索引].动画层[动画层索引].物体[模型索引].缩放.resize(l帧数量);

        for (l帧计数 = 0; l帧计数 < l帧数量; l帧计数++)
        {
            l帧值 = (float)l动画曲线->KeyGetValue(l帧计数);
            l帧时间 = l动画曲线->KeyGetTime(l帧计数);
            l帧时间.GetTime(l时, l分, l秒, l帧, l域, l残值);
            l帧速率 = l帧时间.GetFrameRate(l帧时间.eDefaultMode);

            m动画数据->片段[片段索引].动画层[动画层索引].物体[模型索引].缩放[l帧计数].帧数 =
                l时 * l帧速率 * l帧速率 * l帧速率 + l分 * l帧速率 * l帧速率 + l秒 * l帧速率 + l帧;
            m动画数据->片段[片段索引].动画层[动画层索引].物体[模型索引].缩放[l帧计数].缩放.z = l帧值;
        }
    }

    //显示特定于灯光或标记的曲线。
    FbxNodeAttribute* l节点属性 = p节点->GetNodeAttribute();

    if (l节点属性)
    {
        l动画曲线 = l节点属性->Color.GetCurve(p动画层, FBXSDK_CURVENODE_COLOR_RED);
        if (l动画曲线)
        {
            int l帧数量 = l动画曲线->KeyGetCount();
            if (l帧数量 > m动画数据->片段[片段索引].动画层[动画层索引].物体[模型索引].颜色.size())
                m动画数据->片段[片段索引].动画层[动画层索引].物体[模型索引].颜色.resize(l帧数量);

            for (l帧计数 = 0; l帧计数 < l帧数量; l帧计数++)
            {
                l帧值 = (float)l动画曲线->KeyGetValue(l帧计数);
                l帧时间 = l动画曲线->KeyGetTime(l帧计数);
                l帧时间.GetTime(l时, l分, l秒, l帧, l域, l残值);
                l帧速率 = l帧时间.GetFrameRate(l帧时间.eDefaultMode);

                m动画数据->片段[片段索引].动画层[动画层索引].物体[模型索引].颜色[l帧计数].帧数 =
                    l时 * l帧速率 * l帧速率 * l帧速率 + l分 * l帧速率 * l帧速率 + l秒 * l帧速率 + l帧;
                m动画数据->片段[片段索引].动画层[动画层索引].物体[模型索引].颜色[l帧计数].颜色.x = l帧值;
            }
        }
        l动画曲线 = l节点属性->Color.GetCurve(p动画层, FBXSDK_CURVENODE_COLOR_GREEN);
        if (l动画曲线)
        {
            int l帧数量 = l动画曲线->KeyGetCount();
            if (l帧数量 > m动画数据->片段[片段索引].动画层[动画层索引].物体[模型索引].颜色.size())
                m动画数据->片段[片段索引].动画层[动画层索引].物体[模型索引].颜色.resize(l帧数量);

            for (l帧计数 = 0; l帧计数 < l帧数量; l帧计数++)
            {
                l帧值 = (float)l动画曲线->KeyGetValue(l帧计数);
                l帧时间 = l动画曲线->KeyGetTime(l帧计数);
                l帧时间.GetTime(l时, l分, l秒, l帧, l域, l残值);
                l帧速率 = l帧时间.GetFrameRate(l帧时间.eDefaultMode);

                m动画数据->片段[片段索引].动画层[动画层索引].物体[模型索引].颜色[l帧计数].帧数 =
                    l时 * l帧速率 * l帧速率 * l帧速率 + l分 * l帧速率 * l帧速率 + l秒 * l帧速率 + l帧;
                m动画数据->片段[片段索引].动画层[动画层索引].物体[模型索引].颜色[l帧计数].颜色.y = l帧值;
            }
        }
        l动画曲线 = l节点属性->Color.GetCurve(p动画层, FBXSDK_CURVENODE_COLOR_BLUE);
        if (l动画曲线)
        {
            int l帧数量 = l动画曲线->KeyGetCount();
            if (l帧数量 > m动画数据->片段[片段索引].动画层[动画层索引].物体[模型索引].颜色.size())
                m动画数据->片段[片段索引].动画层[动画层索引].物体[模型索引].颜色.resize(l帧数量);

            for (l帧计数 = 0; l帧计数 < l帧数量; l帧计数++)
            {
                l帧值 = (float)l动画曲线->KeyGetValue(l帧计数);
                l帧时间 = l动画曲线->KeyGetTime(l帧计数);
                l帧时间.GetTime(l时, l分, l秒, l帧, l域, l残值);
                l帧速率 = l帧时间.GetFrameRate(l帧时间.eDefaultMode);

                m动画数据->片段[片段索引].动画层[动画层索引].物体[模型索引].颜色[l帧计数].帧数 =
                    l时 * l帧速率 * l帧速率 * l帧速率 + l分 * l帧速率 * l帧速率 + l秒 * l帧速率 + l帧;
                m动画数据->片段[片段索引].动画层[动画层索引].物体[模型索引].颜色[l帧计数].颜色.z = l帧值;
            }
        }

        //显示特定于灯光的曲线。
        FbxLight* l光源 = p节点->GetLight();
        if (l光源)
        {
            l动画曲线 = l光源->Intensity.GetCurve(p动画层);
            if (l动画曲线)
            {
                int l帧数量 = l动画曲线->KeyGetCount();
                if (l帧数量 > m动画数据->片段[片段索引].动画层[动画层索引].物体[模型索引].灯光属性.size())
                    m动画数据->片段[片段索引].动画层[动画层索引].物体[模型索引].灯光属性.resize(l帧数量);

                for (l帧计数 = 0; l帧计数 < l帧数量; l帧计数++)
                {
                    l帧值 = (float)l动画曲线->KeyGetValue(l帧计数);
                    l帧时间 = l动画曲线->KeyGetTime(l帧计数);
                    l帧时间.GetTime(l时, l分, l秒, l帧, l域, l残值);
                    l帧速率 = l帧时间.GetFrameRate(l帧时间.eDefaultMode);

                    m动画数据->片段[片段索引].动画层[动画层索引].物体[模型索引].灯光属性[l帧计数].帧数 =
                        l时 * l帧速率 * l帧速率 * l帧速率 + l分 * l帧速率 * l帧速率 + l秒 * l帧速率 + l帧;
                    m动画数据->片段[片段索引].动画层[动画层索引].物体[模型索引].灯光属性[l帧计数].强度 = l帧值;
                }
            }

            l动画曲线 = l光源->OuterAngle.GetCurve(p动画层);
            if (l动画曲线)
            {
                int l帧数量 = l动画曲线->KeyGetCount();
                if (l帧数量 > m动画数据->片段[片段索引].动画层[动画层索引].物体[模型索引].灯光属性.size())
                    m动画数据->片段[片段索引].动画层[动画层索引].物体[模型索引].灯光属性.resize(l帧数量);

                for (l帧计数 = 0; l帧计数 < l帧数量; l帧计数++)
                {
                    l帧值 = (float)l动画曲线->KeyGetValue(l帧计数);
                    l帧时间 = l动画曲线->KeyGetTime(l帧计数);
                    l帧时间.GetTime(l时, l分, l秒, l帧, l域, l残值);
                    l帧速率 = l帧时间.GetFrameRate(l帧时间.eDefaultMode);

                    m动画数据->片段[片段索引].动画层[动画层索引].物体[模型索引].灯光属性[l帧计数].帧数 =
                        l时 * l帧速率 * l帧速率 * l帧速率 + l分 * l帧速率 * l帧速率 + l秒 * l帧速率 + l帧;
                    m动画数据->片段[片段索引].动画层[动画层索引].物体[模型索引].灯光属性[l帧计数].外角 = l帧值;
                }
            }

            l动画曲线 = l光源->Fog.GetCurve(p动画层);
            if (l动画曲线)
            {
                int l帧数量 = l动画曲线->KeyGetCount();
                if (l帧数量 > m动画数据->片段[片段索引].动画层[动画层索引].物体[模型索引].灯光属性.size())
                    m动画数据->片段[片段索引].动画层[动画层索引].物体[模型索引].灯光属性.resize(l帧数量);

                for (l帧计数 = 0; l帧计数 < l帧数量; l帧计数++)
                {
                    l帧值 = (float)l动画曲线->KeyGetValue(l帧计数);
                    l帧时间 = l动画曲线->KeyGetTime(l帧计数);
                    l帧时间.GetTime(l时, l分, l秒, l帧, l域, l残值);
                    l帧速率 = l帧时间.GetFrameRate(l帧时间.eDefaultMode);

                    m动画数据->片段[片段索引].动画层[动画层索引].物体[模型索引].灯光属性[l帧计数].帧数 =
                        l时 * l帧速率 * l帧速率 * l帧速率 + l分 * l帧速率 * l帧速率 + l秒 * l帧速率 + l帧;
                    m动画数据->片段[片段索引].动画层[动画层索引].物体[模型索引].灯光属性[l帧计数].雾 = l帧值;
                }
            }
        }

        //显示特定于摄像机的曲线。
        FbxCamera* l相机 = p节点->GetCamera();
        if (l相机)
        {
            l动画曲线 = l相机->FieldOfView.GetCurve(p动画层);
            if (l动画曲线)
            {

            }

            l动画曲线 = l相机->FieldOfViewX.GetCurve(p动画层);
            if (l动画曲线)
            {
            }

            l动画曲线 = l相机->FieldOfViewY.GetCurve(p动画层);
            if (l动画曲线)
            {

            }

            l动画曲线 = l相机->OpticalCenterX.GetCurve(p动画层);
            if (l动画曲线)
            {

            }

            l动画曲线 = l相机->OpticalCenterY.GetCurve(p动画层);
            if (l动画曲线)
            {

            }

            l动画曲线 = l相机->Roll.GetCurve(p动画层);
            if (l动画曲线)
            {

            }
        }

        //显示特定于几何的曲线。
        if (l节点属性->GetAttributeType() == FbxNodeAttribute::eMesh ||
            l节点属性->GetAttributeType() == FbxNodeAttribute::eNurbs ||
            l节点属性->GetAttributeType() == FbxNodeAttribute::ePatch)
        {

        }
    }

    //显示特定于特性的曲线
    FbxProperty l属性 = p节点->GetFirstProperty();
}

void C动态物体::加载骨骼数据(FbxNode* p骨骼节点)
{
    WCHAR* l骨骼名称 = 0;
    size_t l长度;
    SSRT变换 l变换;

    FbxUTF8ToWC(p骨骼节点->GetName(), l骨骼名称, &l长度);

    l变换.缩放.x = p骨骼节点->LclScaling.Get().mData[1];
    l变换.缩放.y = p骨骼节点->LclScaling.Get().mData[2];
    l变换.缩放.z = p骨骼节点->LclScaling.Get().mData[0];
    l变换.旋转.x = p骨骼节点->LclRotation.Get().mData[1];
    l变换.旋转.y = p骨骼节点->LclRotation.Get().mData[2];
    l变换.旋转.z = p骨骼节点->LclRotation.Get().mData[0];
    l变换.位置.x = p骨骼节点->LclTranslation.Get().mData[1];
    l变换.位置.y = p骨骼节点->LclTranslation.Get().mData[2];
    l变换.位置.z = p骨骼节点->LclTranslation.Get().mData[0];

    骨骼数量++;
    m骨骼名称.resize(骨骼数量);
    m骨骼名称[骨骼数量 - 1] = l骨骼名称;
    m骨骼变换.resize(骨骼数量);
    m骨骼变换[骨骼数量 - 1].SRT变换 = l变换;
}

void C动态物体::加载骨骼蒙皮信息(FbxNode* p网格节点)
{
    int i, j, k;
    int l簇数量 = 0;
    int l骨骼数量 = 0;
    FbxCluster* l簇;
    WCHAR* l骨骼名字 = 0;
    WCHAR* l物体名字 = 0;
    XMMATRIX 旋转矩阵 = XMMatrixIdentity();
    XMMATRIX 旋转 = XMMatrixIdentity();

    FbxGeometry* p几何 = (FbxMesh*)p网格节点->GetNodeAttribute();
    l簇数量 = p几何->GetDeformerCount(FbxDeformer::eSkin);
    FbxUTF8ToWC(p网格节点->GetName(), l物体名字, 0);
    m蒙皮数据->关联物体.resize(m蒙皮数据->关联物体.size() + 1);
    m蒙皮数据->关联物体[m蒙皮数据->关联物体.size() - 1].物体名称 = l物体名字;

    for (i = 0; i != l簇数量; i++)
    {
        l骨骼数量 = ((FbxSkin*)p几何->GetDeformer(i, FbxDeformer::eSkin))->GetClusterCount();
        m蒙皮数据->关联物体[m蒙皮数据->关联物体.size() - 1].骨骼.resize(l骨骼数量);
        for (j = 0; j != l骨骼数量; j++)
        {
            l簇 = ((FbxSkin*)p几何->GetDeformer(i, FbxDeformer::eSkin))->GetCluster(j);

            FbxUTF8ToWC(l簇->GetLink()->GetName(), l骨骼名字, 0);
            m蒙皮数据->关联物体[m蒙皮数据->关联物体.size() - 1].骨骼[j].骨骼名称 = l骨骼名字;

            int l索引数量 = l簇->GetControlPointIndicesCount();
            int* l索引 = l簇->GetControlPointIndices();
            double* l权重 = l簇->GetControlPointWeights();

            m蒙皮数据->关联物体[m蒙皮数据->关联物体.size() - 1].骨骼[j].索引组.resize(l索引数量);
            m蒙皮数据->关联物体[m蒙皮数据->关联物体.size() - 1].骨骼[j].权重组.resize(l索引数量);

            for (k = 0; k < l索引数量; k++)
            {
                m蒙皮数据->关联物体[m蒙皮数据->关联物体.size() - 1].骨骼[j].索引组[k] = l索引[k];
                m蒙皮数据->关联物体[m蒙皮数据->关联物体.size() - 1].骨骼[j].权重组[k] = (float)l权重[k];
            }

            FbxAMatrix l矩阵;

            l矩阵 = l簇->GetTransformMatrix(l矩阵);
            m蒙皮数据->关联物体[m蒙皮数据->关联物体.size() - 1].骨骼[j].关联模型位置.x = l矩阵.GetT().mData[0];
            m蒙皮数据->关联物体[m蒙皮数据->关联物体.size() - 1].骨骼[j].关联模型位置.y = l矩阵.GetT().mData[1];
            m蒙皮数据->关联物体[m蒙皮数据->关联物体.size() - 1].骨骼[j].关联模型位置.z = l矩阵.GetT().mData[2];
            m蒙皮数据->关联物体[m蒙皮数据->关联物体.size() - 1].骨骼[j].关联模型旋转.x = l矩阵.GetR().mData[0];
            m蒙皮数据->关联物体[m蒙皮数据->关联物体.size() - 1].骨骼[j].关联模型旋转.y = l矩阵.GetR().mData[1];
            m蒙皮数据->关联物体[m蒙皮数据->关联物体.size() - 1].骨骼[j].关联模型旋转.z = l矩阵.GetR().mData[2];
            m蒙皮数据->关联物体[m蒙皮数据->关联物体.size() - 1].骨骼[j].关联模型缩放.x = l矩阵.GetS().mData[0];
            m蒙皮数据->关联物体[m蒙皮数据->关联物体.size() - 1].骨骼[j].关联模型缩放.y = l矩阵.GetS().mData[1];
            m蒙皮数据->关联物体[m蒙皮数据->关联物体.size() - 1].骨骼[j].关联模型缩放.z = l矩阵.GetS().mData[2];

            l矩阵 = l簇->GetTransformLinkMatrix(l矩阵);
            旋转矩阵.r[0].m128_f32[0] = l矩阵.mData[1][0]; 旋转矩阵.r[0].m128_f32[1] = l矩阵.mData[1][1]; 
            旋转矩阵.r[0].m128_f32[2] = l矩阵.mData[1][2];
            旋转矩阵.r[1].m128_f32[0] = l矩阵.mData[2][0]; 旋转矩阵.r[1].m128_f32[1] = l矩阵.mData[2][1];
            旋转矩阵.r[1].m128_f32[2] = l矩阵.mData[2][2];
            旋转矩阵.r[2].m128_f32[0] = l矩阵.mData[0][0]; 旋转矩阵.r[2].m128_f32[1] = l矩阵.mData[0][1];
            旋转矩阵.r[2].m128_f32[2] = l矩阵.mData[0][2];
            旋转矩阵.r[3].m128_f32[0] = l矩阵.mData[3][0]; 旋转矩阵.r[3].m128_f32[1] = l矩阵.mData[3][1];
            旋转矩阵.r[3].m128_f32[2] = l矩阵.mData[3][2];
            旋转 = XMMatrixRotationY(-90 * XM_PI / 180);
            旋转矩阵 = 旋转矩阵 * 旋转;
            旋转矩阵.r[3].m128_f32[0] = l矩阵.mData[3][2]; 旋转矩阵.r[3].m128_f32[1] = l矩阵.mData[3][1];
            旋转矩阵.r[3].m128_f32[2] = -l矩阵.mData[3][0];

            m蒙皮数据->关联物体[m蒙皮数据->关联物体.size() - 1].骨骼[j].关联骨骼旋转矩阵 = 旋转矩阵;
            m蒙皮数据->关联物体[m蒙皮数据->关联物体.size() - 1].骨骼[j].关联骨骼位置.x = -l矩阵.GetT().mData[2];
            m蒙皮数据->关联物体[m蒙皮数据->关联物体.size() - 1].骨骼[j].关联骨骼位置.y = l矩阵.GetT().mData[1];
            m蒙皮数据->关联物体[m蒙皮数据->关联物体.size() - 1].骨骼[j].关联骨骼位置.z = l矩阵.GetT().mData[0];
            m蒙皮数据->关联物体[m蒙皮数据->关联物体.size() - 1].骨骼[j].关联骨骼旋转.x = l矩阵.GetR().mData[2];
            m蒙皮数据->关联物体[m蒙皮数据->关联物体.size() - 1].骨骼[j].关联骨骼旋转.y = l矩阵.GetR().mData[1];
            m蒙皮数据->关联物体[m蒙皮数据->关联物体.size() - 1].骨骼[j].关联骨骼旋转.z = l矩阵.GetR().mData[0];
            m蒙皮数据->关联物体[m蒙皮数据->关联物体.size() - 1].骨骼[j].关联骨骼缩放.x = l矩阵.GetS().mData[2];
            m蒙皮数据->关联物体[m蒙皮数据->关联物体.size() - 1].骨骼[j].关联骨骼缩放.y = l矩阵.GetS().mData[1];
            m蒙皮数据->关联物体[m蒙皮数据->关联物体.size() - 1].骨骼[j].关联骨骼缩放.z = l矩阵.GetS().mData[0];
        }
    }

    l簇数量 = p几何->GetDeformerCount(FbxDeformer::eBlendShape);

    for (int i = 0; i < l簇数量; i++)
    {
        l骨骼数量 = ((FbxSkin*)p几何->GetDeformer(i, FbxDeformer::eSkin))->GetClusterCount();
    }
}

void C动态物体::加载造型(FbxScene* p场景)
{
    int      i, j, k, l造型数量;
    FbxString  l名称;
    FbxNode* l节点 = nullptr;
    WCHAR* 造型名称 = nullptr;
    造型 = new S造型;

    l造型数量 = p场景->GetPoseCount();

    for (i = 0; i < l造型数量; i++)
    {
        FbxPose* l造型 = p场景->GetPose(i);

        l名称 = l造型->GetName();
        FbxUTF8ToWC(l造型->GetName(), 造型名称, 0);

        for (j = 0; j < l造型->GetCount(); j++)
        {

            l名称 = l造型->GetNodeName(j).GetCurrentName();
            FbxUTF8ToWC(l造型->GetNodeName(j).GetCurrentName(), 造型名称, 0);

            FbxString lMatrixValue;
            XMMATRIX 绑定矩阵 = XMMatrixIdentity();

            for (k = 0; k < 4; k++)
            {
                FbxMatrix  l矩阵 = l造型->GetMatrix(j);
                FbxVector4 l行 = l矩阵.GetRow(k);

                绑定矩阵.r[k].m128_f32[0] = l行[0]; 绑定矩阵.r[k].m128_f32[1] = l行[1];
                绑定矩阵.r[k].m128_f32[2] = l行[2]; 绑定矩阵.r[k].m128_f32[3] = l行[3];
            }

            XMVECTOR 造型位置{};
            造型位置.m128_f32[0] = -绑定矩阵.r[3].m128_f32[2]; 造型位置.m128_f32[1] = 绑定矩阵.r[3].m128_f32[1];
            造型位置.m128_f32[2] = 绑定矩阵.r[3].m128_f32[0];

            绑定矩阵.r[1].m128_f32[0] = -绑定矩阵.r[1].m128_f32[0]; 绑定矩阵.r[1].m128_f32[1] = -绑定矩阵.r[1].m128_f32[1];
            绑定矩阵.r[1].m128_f32[2] = -绑定矩阵.r[1].m128_f32[2];
            绑定矩阵.r[0].m128_f32[2] = -绑定矩阵.r[0].m128_f32[2]; 绑定矩阵.r[1].m128_f32[2] = -绑定矩阵.r[1].m128_f32[2];
            绑定矩阵.r[2].m128_f32[2] = -绑定矩阵.r[2].m128_f32[2];

            XMMATRIX 绑定矩阵2 = 绑定矩阵;

            绑定矩阵2.r[0].m128_f32[0] = 绑定矩阵.r[0].m128_f32[2]; 绑定矩阵2.r[1].m128_f32[0] = 绑定矩阵.r[1].m128_f32[2];
            绑定矩阵2.r[2].m128_f32[0] = 绑定矩阵.r[2].m128_f32[2]; 
            绑定矩阵2.r[0].m128_f32[2] = 绑定矩阵.r[0].m128_f32[0]; 绑定矩阵2.r[1].m128_f32[2] = 绑定矩阵.r[1].m128_f32[0];
            绑定矩阵2.r[2].m128_f32[2] = 绑定矩阵.r[2].m128_f32[0]; 

            绑定矩阵 = 绑定矩阵2;

            绑定矩阵2.r[0].m128_f32[0] = -绑定矩阵.r[1].m128_f32[0]; 绑定矩阵2.r[0].m128_f32[1] = -绑定矩阵.r[1].m128_f32[1];
            绑定矩阵2.r[0].m128_f32[2] = -绑定矩阵.r[1].m128_f32[2];
            绑定矩阵2.r[1].m128_f32[0] = 绑定矩阵.r[2].m128_f32[0]; 绑定矩阵2.r[1].m128_f32[1] = 绑定矩阵.r[2].m128_f32[1];
            绑定矩阵2.r[1].m128_f32[2] = 绑定矩阵.r[2].m128_f32[2];
            绑定矩阵2.r[2].m128_f32[0] = 绑定矩阵.r[0].m128_f32[0]; 绑定矩阵2.r[2].m128_f32[1] = 绑定矩阵.r[0].m128_f32[1];
            绑定矩阵2.r[2].m128_f32[2] = 绑定矩阵.r[0].m128_f32[2];

            绑定矩阵2.r[3].m128_f32[0] = 造型位置.m128_f32[0]; 绑定矩阵2.r[3].m128_f32[1] = 造型位置.m128_f32[1];
            绑定矩阵2.r[3].m128_f32[2] = 造型位置.m128_f32[2];

            造型->绑定造型.insert(pair<wstring, XMMATRIX>(造型名称, 绑定矩阵2));
        }
    }

    XMMATRIX 绑定矩阵 = XMMatrixIdentity();
    造型->绑定造型.insert(pair<wstring, XMMATRIX>(L"根节点", 绑定矩阵));

    l造型数量 = p场景->GetCharacterPoseCount();

    for (i = 0; i < l造型数量; i++)
    {
        FbxCharacterPose* l造型 = p场景->GetCharacterPose(i);
        FbxCharacter* l角色 = l造型->GetCharacter();

        if (!l角色) break;

        FbxUTF8ToWC(l角色->GetName(), 造型名称, 0);

        FbxCharacterLink l角色连接;
        FbxCharacter::ENodeId  l节点id = FbxCharacter::eHips;

        while (l角色->GetCharacterLink(l节点id, &l角色连接))
        {
            FbxAMatrix& lGlobalPosition = l角色连接.mNode->EvaluateGlobalTransform(FBXSDK_TIME_ZERO);

            FbxString lMatrixValue;
            XMMATRIX 角色造型 = XMMatrixIdentity();

            for (k = 0; k < 4; k++)
            {
                FbxVector4 lRow = lGlobalPosition.GetRow(k);

                角色造型.r[k].m128_f32[0] = lRow[0]; 角色造型.r[k].m128_f32[1] = lRow[1];
                角色造型.r[k].m128_f32[2] = lRow[2]; 角色造型.r[k].m128_f32[3] = lRow[3];
            }

            XMMATRIX 角色造型2 = XMMatrixIdentity();

            XMVECTOR 造型位置{};
            造型位置.m128_f32[0] = -角色造型.r[3].m128_f32[2]; 造型位置.m128_f32[1] = 角色造型.r[3].m128_f32[1];
            造型位置.m128_f32[2] = 角色造型.r[3].m128_f32[0];

            角色造型.r[1].m128_f32[0] = -角色造型.r[1].m128_f32[0]; 角色造型.r[1].m128_f32[1] = -角色造型.r[1].m128_f32[1];
            角色造型.r[1].m128_f32[2] = -角色造型.r[1].m128_f32[2];
            角色造型.r[0].m128_f32[2] = -角色造型.r[0].m128_f32[2]; 角色造型.r[1].m128_f32[2] = -角色造型.r[1].m128_f32[2];
            角色造型.r[2].m128_f32[2] = -角色造型.r[2].m128_f32[2];

            角色造型2 = 角色造型;

            角色造型2.r[0].m128_f32[0] = 角色造型.r[0].m128_f32[2]; 角色造型2.r[1].m128_f32[0] = 角色造型.r[1].m128_f32[2];
            角色造型2.r[2].m128_f32[0] = 角色造型.r[2].m128_f32[2];
            角色造型2.r[0].m128_f32[2] = 角色造型.r[0].m128_f32[0]; 角色造型2.r[1].m128_f32[2] = 角色造型.r[1].m128_f32[0];
            角色造型2.r[2].m128_f32[2] = 角色造型.r[2].m128_f32[0];

            角色造型 = 角色造型2;

            角色造型2.r[0].m128_f32[0] = -角色造型.r[1].m128_f32[0]; 角色造型2.r[0].m128_f32[1] = 角色造型.r[1].m128_f32[1];
            角色造型2.r[0].m128_f32[2] = 角色造型.r[1].m128_f32[2];
            角色造型2.r[1].m128_f32[0] = 角色造型.r[2].m128_f32[0]; 角色造型2.r[1].m128_f32[1] = 角色造型.r[2].m128_f32[1];
            角色造型2.r[1].m128_f32[2] = 角色造型.r[2].m128_f32[2];
            角色造型2.r[2].m128_f32[0] = -角色造型.r[0].m128_f32[0]; 角色造型2.r[2].m128_f32[1] = 角色造型.r[0].m128_f32[1];
            角色造型2.r[2].m128_f32[2] = 角色造型.r[0].m128_f32[2];

            角色造型.r[3].m128_f32[0] = 造型位置.m128_f32[0]; 角色造型.r[3].m128_f32[1] = 造型位置.m128_f32[1];
            角色造型.r[3].m128_f32[2] = 造型位置.m128_f32[2];

            造型->角色造型.insert(pair<wstring, XMMATRIX>(造型名称, 角色造型));

            l节点id = FbxCharacter::ENodeId(int(l节点id) + 1);
        }
    }

    绑定矩阵 = XMMatrixIdentity();
    造型->角色造型.insert(pair<wstring, XMMATRIX>(L"根节点", 绑定矩阵));
}

void C动态物体::加载骨骼位置信息()
{
    int i = 0;
    int j = 0;
    XMFLOAT3 节点位置{};
    XMMATRIX 世界矩阵 = XMMatrixIdentity();

    for (i = 0; i < m根节点->子节点数量; i++)
    {
        for (j = 0; j < m骨骼名称.size(); j++)
        {
            if (m骨骼名称[j] == m根节点->子节点[i].节点名称)
            {
                m根节点->子节点[i].原始位置 = m根节点->子节点[i].变换.位置;
                加载骨骼位置信息(&m根节点->子节点[i], 世界矩阵);
            }
        }
    }
}

void C动态物体::加载骨骼位置信息(S变换节点* p节点, XMMATRIX 世界矩阵)
{
    int i = 0;
    int j = 0;
    int k = 0;
    SSRT变换 变换;
    XMVECTOR 位置{};
    XMVECTOR 旋转{};
    XMMATRIX 变换矩阵{};
    XMMATRIX 世界旋转{};

    wstring 骨骼名称 = p节点->节点名称;
    世界旋转 = 世界矩阵;

    变换.缩放 = p节点->变换.缩放;
    变换.旋转.x = p节点->父节点->变换.旋转.x;
    变换.旋转.y = p节点->父节点->变换.旋转.y;
    变换.旋转.z = p节点->父节点->变换.旋转.z;
    变换矩阵 = XMMatrixRotationRollPitchYaw(变换.旋转.x * XM_PI / 180,
        变换.旋转.y * XM_PI / 180, 变换.旋转.z * XM_PI / 180);
    p节点->原始位置 = p节点->变换.位置;
    变换.旋转.x = p节点->变换.旋转.x;
    变换.旋转.y = p节点->变换.旋转.y;
    变换.旋转.z = p节点->变换.旋转.z;
    p节点->原始旋转 = 变换.旋转;
    世界旋转 = 变换矩阵 * 世界矩阵;
    p节点->世界矩阵 = 世界旋转;
    位置.m128_f32[0] = p节点->变换.位置.x;
    位置.m128_f32[1] = p节点->变换.位置.y;
    位置.m128_f32[2] = p节点->变换.位置.z;
    位置 = XMVector3TransformCoord(位置, 世界旋转);
    位置.m128_f32[0] += p节点->父节点->变换.位置.x;
    位置.m128_f32[1] += p节点->父节点->变换.位置.y;
    位置.m128_f32[2] += p节点->父节点->变换.位置.z;
    变换.位置.x = 位置.m128_f32[0];
    变换.位置.y = 位置.m128_f32[1];
    变换.位置.z = 位置.m128_f32[2];
    XMStoreFloat3(&变换.位置, 位置);
    变换.旋转 = p节点->变换.旋转;
    p节点->变换.位置.x = 变换.位置.x;
    p节点->变换.位置.y = 变换.位置.y;
    p节点->变换.位置.z = 变换.位置.z;

    for (j = 0; j < m骨骼变换.size(); j++)
    {
        if (m骨骼名称[j] == p节点->节点名称)
        {
            m骨骼变换[j].SRT变换.位置 = 变换.位置;
            XMStoreFloat3x3(&m骨骼变换[j].旋转, 世界旋转);
        }
    }

    for(i = 0; i < p节点->子节点数量; i++)
        加载骨骼位置信息(&p节点->子节点[i], 世界旋转);
}

void C动态物体::搜索骨骼树(wstring 骨骼名称, S变换节点*& 目标节点)
{
    int i = 0;

    for (i = 0; i < m根节点->子节点数量; i++)
    {
        搜索骨骼树(&m根节点->子节点[i], 骨骼名称, 目标节点);
    }
}

void C动态物体::搜索骨骼树(S变换节点* 变换节点, wstring 骨骼名称, S变换节点*& 目标节点)
{
    int i = 0;

    if (变换节点->节点名称 == 骨骼名称)
    {
        目标节点 = 变换节点;
        return;
    }

    for (i = 0; i < 变换节点->子节点数量; i++)
    {
        搜索骨骼树(&变换节点->子节点[i], 骨骼名称, 目标节点);
    }
}

void C动态物体::设定轨道数(S变换节点* 变换节点, UINT 轨道数)
{
    变换节点->动画轨道.resize(轨道数);

    for (int i = 0; i < 变换节点->子节点数量; i++)
    {
        设定轨道数(&变换节点->子节点[i], 轨道数);
    }
}

void C动态物体::设定帧数(S变换节点* 变换节点, UINT 轨道, UINT 帧数)
{
    变换节点->动画轨道[轨道].帧.resize(帧数);

    for (int i = 0; i < 变换节点->子节点数量; i++)
    {
        设定帧数(&变换节点->子节点[i], 轨道, 帧数);
    }
}

void C动态物体::合并物体动画信息()
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
    XMMATRIX 变换矩阵 = XMMatrixIdentity();
    XMMATRIX 变换矩阵2 = XMMatrixIdentity();
    XMMATRIX 旋转变换 = XMMatrixIdentity();
    XMVECTOR l旋转向量{};
    XMVECTOR l旋转向量2{};
    XMVECTOR 位置{};
    XMVECTOR 旋转{};
    XMVECTOR 缩放{};
    XMFLOAT3X3 旋转矩阵{};
    XMFLOAT4X3 初始矩阵{};
    float l帧比例 = 0;
    float l变化数 = 0;
    UINT l当前物体计数 = 0;
    S变换节点* 骨骼节点;
    UINT 帧偏移 = 0;
    bool 是否为零矩阵 = false;

    XMStoreFloat4x3(&初始矩阵, XMMatrixIdentity());

    动画轨道.resize(m动画数据->片段.size());
    for (i = 0; i < 动画轨道.size(); i++)
    {
        动画轨道[i].原始时长 = (float)(m动画数据->片段[i].结束帧 - m动画数据->片段[i].开始帧 + 1) / m动画数据->片段[i].帧速率;
        动画轨道[i].帧.resize(m动画数据->片段[i].结束帧 - m动画数据->片段[i].开始帧 + 1);
        动画轨道[i].是否循环 = 1;
        动画轨道[i].轨道名称 = m动画数据->片段[i].片段名称;
        动画轨道[i].速度 = 1.0f;
        帧偏移 = m动画数据->片段[i].开始帧;

        设定轨道数(m根节点, m动画数据->片段.size());
        设定帧数(m根节点, i, 动画轨道[i].帧.size());

        for (j = 帧偏移; j < 动画轨道[i].帧.size() + 帧偏移; j++)
        {
            动画轨道[i].帧[j - 帧偏移].骨骼变换.resize(骨骼数量, 初始矩阵);
            动画轨道[i].帧[j - 帧偏移].物体变换.resize(属性->元素.size(), 初始矩阵);

            for (k = 0; k < m动画数据->片段[i].动画层.size(); k++)
            {
                for (m = 0; m < m动画数据->片段[i].动画层[k].物体.size(); m++)
                {
                    //加载物体变换
                    for (n = 0; n < 属性->元素.size(); n++)
                    {
                        if (m动画数据->片段[i].动画层[k].物体[m].物体名称.compare(属性->元素[n]->物体名称) == 0)
                        {
                            if (m动画数据->片段[i].动画层[k].物体[m].位置.size() == 0)
                            {
                                是否为零矩阵 = true;
                                for (x = 0; x < 4; x++)
                                    for (y = 0; y < 4; y++)
                                        if (造型->绑定造型[属性->元素[n]->物体名称].r[x].m128_f32[y] != 0.0f) 是否为零矩阵 = false;
                                if (是否为零矩阵)
                                    XMStoreFloat4x3(&动画轨道[i].帧[j - 帧偏移].物体变换[n], 属性->元素[n]->变换);
                                else
                                    XMStoreFloat4x3(&动画轨道[i].帧[j - 帧偏移].物体变换[n], 造型->绑定造型[属性->元素[n]->物体名称]);
                            }

                            //位置变换
                            //在帧前或前帧上
                            if (m动画数据->片段[i].动画层[k].物体[m].位置.size() != 0)
                                if (m动画数据->片段[i].动画层[k].物体[m].位置[0].帧数 >= j)
                                {
                                    动画轨道[i].帧[j - 帧偏移].物体变换[n].m[3][2] = m动画数据->片段[i].动画层[k].物体[m].位置[0].位置.x;
                                    动画轨道[i].帧[j - 帧偏移].物体变换[n].m[3][1] = m动画数据->片段[i].动画层[k].物体[m].位置[0].位置.y;
                                    动画轨道[i].帧[j - 帧偏移].物体变换[n].m[3][0] = m动画数据->片段[i].动画层[k].物体[m].位置[0].位置.z;
                                }

                            for (u = 0; u < m动画数据->片段[i].动画层[k].物体[m].位置.size(); u++)
                            {
                                //在帧区间内
                                if (u + 1 < m动画数据->片段[i].动画层[k].物体[m].位置.size())
                                    if (m动画数据->片段[i].动画层[k].物体[m].位置[u].帧数 <= j &&
                                        m动画数据->片段[i].动画层[k].物体[m].位置[u + 1].帧数 > j)
                                    {
                                        l帧比例 = ((float)j - m动画数据->片段[i].动画层[k].物体[m].位置[u].帧数) /
                                            (m动画数据->片段[i].动画层[k].物体[m].位置[u + 1].帧数 -
                                                m动画数据->片段[i].动画层[k].物体[m].位置[u].帧数);
                                        位置.m128_f32[2] = (m动画数据->片段[i].动画层[k].物体[m].位置[u + 1].位置.x -
                                            m动画数据->片段[i].动画层[k].物体[m].位置[u].位置.x) * l帧比例 +
                                            m动画数据->片段[i].动画层[k].物体[m].位置[u].位置.x;
                                        位置.m128_f32[1] = (m动画数据->片段[i].动画层[k].物体[m].位置[u + 1].位置.y -
                                            m动画数据->片段[i].动画层[k].物体[m].位置[u].位置.y) * l帧比例 +
                                            m动画数据->片段[i].动画层[k].物体[m].位置[u].位置.y;
                                        位置.m128_f32[0] = -((m动画数据->片段[i].动画层[k].物体[m].位置[u + 1].位置.z -
                                            m动画数据->片段[i].动画层[k].物体[m].位置[u].位置.z) * l帧比例 +
                                            m动画数据->片段[i].动画层[k].物体[m].位置[u].位置.z);

                                        动画轨道[i].帧[j - 帧偏移].物体变换[n].m[3][0] = 位置.m128_f32[0];
                                        动画轨道[i].帧[j - 帧偏移].物体变换[n].m[3][1] = 位置.m128_f32[1];
                                        动画轨道[i].帧[j - 帧偏移].物体变换[n].m[3][2] = 位置.m128_f32[2];
                                    }
                            }

                            //在帧区间后或后帧上
                            if (m动画数据->片段[i].动画层[k].物体[m].位置.size() > 0)
                                if (m动画数据->片段[i].动画层[k].物体[m].位置[m动画数据->片段[i].动画层[k].物体[m].位置.size() - 1].帧数 <= j)
                                {
                                    位置.m128_f32[2] = m动画数据->片段[i].动画层[k].物体[m].位置[
                                        m动画数据->片段[i].动画层[k].物体[m].位置.size() - 1].位置.x;
                                    位置.m128_f32[1] = m动画数据->片段[i].动画层[k].物体[m].位置[
                                        m动画数据->片段[i].动画层[k].物体[m].位置.size() - 1].位置.y;
                                    位置.m128_f32[0] = -m动画数据->片段[i].动画层[k].物体[m].位置[
                                        m动画数据->片段[i].动画层[k].物体[m].位置.size() - 1].位置.z;

                                    动画轨道[i].帧[j - 帧偏移].物体变换[n].m[3][0] = 位置.m128_f32[0];
                                    动画轨道[i].帧[j - 帧偏移].物体变换[n].m[3][1] = 位置.m128_f32[1];
                                    动画轨道[i].帧[j - 帧偏移].物体变换[n].m[3][2] = 位置.m128_f32[2];
                                }

                            //旋转变换
                            if (m动画数据->片段[i].动画层[k].物体[m].旋转.size() == 0)
                            {
                                是否为零矩阵 = true;
                                for (x = 0; x < 4; x++)
                                    for (y = 0; y < 4; y++)
                                        if (造型->绑定造型[属性->元素[n]->物体名称].r[x].m128_f32[y] != 0.0f) 是否为零矩阵 = false;
                                if (是否为零矩阵)
                                    XMStoreFloat4x3(&动画轨道[i].帧[j - 帧偏移].物体变换[n], 属性->元素[n]->变换);
                                else
                                XMStoreFloat4x3(&动画轨道[i].帧[j - 帧偏移].物体变换[n], 造型->绑定造型[属性->元素[n]->物体名称]);
                            }

                            //在帧前或帧上
                            if (m动画数据->片段[i].动画层[k].物体[m].旋转.size() != 0)
                                if (m动画数据->片段[i].动画层[k].物体[m].旋转[0].帧数 >= j)
                                {
                                    旋转.m128_f32[0] = m动画数据->片段[i].动画层[k].物体[m].旋转[0].旋转.x * XM_PI / 180;
                                    旋转.m128_f32[1] = m动画数据->片段[i].动画层[k].物体[m].旋转[0].旋转.y * XM_PI / 180;
                                    旋转.m128_f32[2] = m动画数据->片段[i].动画层[k].物体[m].旋转[0].旋转.z * XM_PI / 180;

                                    旋转变换 = XMMatrixRotationRollPitchYaw(旋转.m128_f32[1], 旋转.m128_f32[2], 旋转.m128_f32[0]);

                                    动画轨道[i].帧[j - 帧偏移].物体变换[n].m[0][0] = 旋转变换.r[0].m128_f32[0];
                                    动画轨道[i].帧[j - 帧偏移].物体变换[n].m[0][1] = 旋转变换.r[0].m128_f32[1];
                                    动画轨道[i].帧[j - 帧偏移].物体变换[n].m[0][2] = 旋转变换.r[0].m128_f32[2];
                                    动画轨道[i].帧[j - 帧偏移].物体变换[n].m[1][0] = 旋转变换.r[1].m128_f32[0];
                                    动画轨道[i].帧[j - 帧偏移].物体变换[n].m[1][1] = 旋转变换.r[1].m128_f32[1];
                                    动画轨道[i].帧[j - 帧偏移].物体变换[n].m[1][2] = 旋转变换.r[1].m128_f32[2];
                                    动画轨道[i].帧[j - 帧偏移].物体变换[n].m[2][0] = 旋转变换.r[2].m128_f32[0];
                                    动画轨道[i].帧[j - 帧偏移].物体变换[n].m[2][1] = 旋转变换.r[2].m128_f32[1];
                                    动画轨道[i].帧[j - 帧偏移].物体变换[n].m[2][2] = 旋转变换.r[2].m128_f32[2];
                                }

                            for (u = 0; u < m动画数据->片段[i].动画层[k].物体[m].旋转.size(); u++)
                            {
                                //在帧区间内
                                if (u + 1 < m动画数据->片段[i].动画层[k].物体[m].旋转.size())
                                    if (m动画数据->片段[i].动画层[k].物体[m].旋转[u].帧数 <= j && m动画数据->片段[i].动画层[k].物体[m].旋转[u + 1].帧数 > j)
                                    {
                                        l帧比例 = ((float)j - m动画数据->片段[i].动画层[k].物体[m].旋转[u].帧数) /
                                            (m动画数据->片段[i].动画层[k].物体[m].旋转[u + 1].帧数 -
                                                m动画数据->片段[i].动画层[k].物体[m].旋转[u].帧数);

                                        l旋转向量.m128_f32[0] = m动画数据->片段[i].动画层[k].物体[m].旋转[u].旋转.x;
                                        l旋转向量.m128_f32[1] = m动画数据->片段[i].动画层[k].物体[m].旋转[u].旋转.y;
                                        l旋转向量.m128_f32[2] = m动画数据->片段[i].动画层[k].物体[m].旋转[u].旋转.z;
                                        l旋转向量2.m128_f32[0] = m动画数据->片段[i].动画层[k].物体[m].旋转[u + 1].旋转.x;
                                        l旋转向量2.m128_f32[1] = m动画数据->片段[i].动画层[k].物体[m].旋转[u + 1].旋转.y;
                                        l旋转向量2.m128_f32[2] = m动画数据->片段[i].动画层[k].物体[m].旋转[u + 1].旋转.z;

                                        l旋转向量 = (l旋转向量2 - l旋转向量) * l帧比例 + l旋转向量;

                                        旋转.m128_f32[0] = l旋转向量.m128_f32[0] * XM_PI / 180;
                                        旋转.m128_f32[1] = l旋转向量.m128_f32[1] * XM_PI / 180;
                                        旋转.m128_f32[2] = l旋转向量.m128_f32[2] * XM_PI / 180;
                                        旋转变换 = XMMatrixRotationRollPitchYaw(旋转.m128_f32[1], 旋转.m128_f32[2], 旋转.m128_f32[0]);

                                        动画轨道[i].帧[j - 帧偏移].物体变换[n].m[0][0] = 旋转变换.r[0].m128_f32[0];
                                        动画轨道[i].帧[j - 帧偏移].物体变换[n].m[0][1] = 旋转变换.r[0].m128_f32[1];
                                        动画轨道[i].帧[j - 帧偏移].物体变换[n].m[0][2] = 旋转变换.r[0].m128_f32[2];
                                        动画轨道[i].帧[j - 帧偏移].物体变换[n].m[1][0] = 旋转变换.r[1].m128_f32[0];
                                        动画轨道[i].帧[j - 帧偏移].物体变换[n].m[1][1] = 旋转变换.r[1].m128_f32[1];
                                        动画轨道[i].帧[j - 帧偏移].物体变换[n].m[1][2] = 旋转变换.r[1].m128_f32[2];
                                        动画轨道[i].帧[j - 帧偏移].物体变换[n].m[2][0] = 旋转变换.r[2].m128_f32[0];
                                        动画轨道[i].帧[j - 帧偏移].物体变换[n].m[2][1] = 旋转变换.r[2].m128_f32[1];
                                        动画轨道[i].帧[j - 帧偏移].物体变换[n].m[2][2] = 旋转变换.r[2].m128_f32[2];
                                    }
                            }

                            //在帧区间后
                            if (m动画数据->片段[i].动画层[k].物体[m].旋转.size() > 0)
                                if (m动画数据->片段[i].动画层[k].物体[m].旋转[m动画数据->片段[i].动画层[k].物体[m].旋转.size() - 1].帧数 <= j)
                                {
                                    旋转.m128_f32[0] = XM_PI / 180 * m动画数据->片段[i].动画层[k].物体[m].旋转[
                                        m动画数据->片段[i].动画层[k].物体[m].旋转.size() - 1].旋转.x;
                                    旋转.m128_f32[1] = XM_PI / 180 * m动画数据->片段[i].动画层[k].物体[m].旋转[
                                        m动画数据->片段[i].动画层[k].物体[m].旋转.size() - 1].旋转.y;
                                    旋转.m128_f32[2] = XM_PI / 180 * m动画数据->片段[i].动画层[k].物体[m].旋转[
                                        m动画数据->片段[i].动画层[k].物体[m].旋转.size() - 1].旋转.z;

                                    旋转变换 = XMMatrixRotationRollPitchYaw(旋转.m128_f32[1], 旋转.m128_f32[2], 旋转.m128_f32[0]);

                                    动画轨道[i].帧[j - 帧偏移].物体变换[n].m[0][0] = 旋转变换.r[0].m128_f32[0];
                                    动画轨道[i].帧[j - 帧偏移].物体变换[n].m[0][1] = 旋转变换.r[0].m128_f32[1];
                                    动画轨道[i].帧[j - 帧偏移].物体变换[n].m[0][2] = 旋转变换.r[0].m128_f32[2];
                                    动画轨道[i].帧[j - 帧偏移].物体变换[n].m[1][0] = 旋转变换.r[1].m128_f32[0];
                                    动画轨道[i].帧[j - 帧偏移].物体变换[n].m[1][1] = 旋转变换.r[1].m128_f32[1];
                                    动画轨道[i].帧[j - 帧偏移].物体变换[n].m[1][2] = 旋转变换.r[1].m128_f32[2];
                                    动画轨道[i].帧[j - 帧偏移].物体变换[n].m[2][0] = 旋转变换.r[2].m128_f32[0];
                                    动画轨道[i].帧[j - 帧偏移].物体变换[n].m[2][1] = 旋转变换.r[2].m128_f32[1];
                                    动画轨道[i].帧[j - 帧偏移].物体变换[n].m[2][2] = 旋转变换.r[2].m128_f32[2];
                                }

                            //缩放变换
                            if (m动画数据->片段[i].动画层[k].物体[m].缩放.size() == 0)
                            {
                                是否为零矩阵 = true;
                                for (x = 0; x < 4; x++)
                                    for (y = 0; y < 4; y++)
                                        if (造型->绑定造型[属性->元素[n]->物体名称].r[x].m128_f32[y] != 0.0f) 是否为零矩阵 = false;
                                if (是否为零矩阵)
                                    XMStoreFloat4x3(&动画轨道[i].帧[j - 帧偏移].物体变换[n], 属性->元素[n]->变换);
                                else
                                    XMStoreFloat4x3(&动画轨道[i].帧[j - 帧偏移].物体变换[n], 造型->绑定造型[属性->元素[n]->物体名称]);
                            }
                            // 
                            //在帧前或前帧上
                            if (m动画数据->片段[i].动画层[k].物体[m].缩放.size() != 0)
                                if (m动画数据->片段[i].动画层[k].物体[m].缩放[m动画数据->片段[i].动画层[k].物体[m].缩放.size() - 1].帧数 >= j)
                                {
                                    缩放.m128_f32[0] = m动画数据->片段[i].动画层[k].物体[m].缩放[0].缩放.x;
                                    缩放.m128_f32[1] = m动画数据->片段[i].动画层[k].物体[m].缩放[0].缩放.y;
                                    缩放.m128_f32[2] = m动画数据->片段[i].动画层[k].物体[m].缩放[0].缩放.z;

                                    变换矩阵 = XMMatrixScaling(缩放.m128_f32[1], 缩放.m128_f32[0], 缩放.m128_f32[2]);
                                    变换矩阵2 = XMLoadFloat4x3(&动画轨道[i].帧[j - 帧偏移].物体变换[n]);
                                    变换矩阵 *= 变换矩阵2;

                                    动画轨道[i].帧[j - 帧偏移].物体变换[n].m[0][0] = 变换矩阵.r[0].m128_f32[0];
                                    动画轨道[i].帧[j - 帧偏移].物体变换[n].m[0][1] = 变换矩阵.r[0].m128_f32[1];
                                    动画轨道[i].帧[j - 帧偏移].物体变换[n].m[0][2] = 变换矩阵.r[0].m128_f32[2];
                                    动画轨道[i].帧[j - 帧偏移].物体变换[n].m[1][0] = 变换矩阵.r[1].m128_f32[0];
                                    动画轨道[i].帧[j - 帧偏移].物体变换[n].m[1][1] = 变换矩阵.r[1].m128_f32[1];
                                    动画轨道[i].帧[j - 帧偏移].物体变换[n].m[1][2] = 变换矩阵.r[1].m128_f32[2];
                                    动画轨道[i].帧[j - 帧偏移].物体变换[n].m[2][0] = 变换矩阵.r[2].m128_f32[0];
                                    动画轨道[i].帧[j - 帧偏移].物体变换[n].m[2][1] = 变换矩阵.r[2].m128_f32[1];
                                    动画轨道[i].帧[j - 帧偏移].物体变换[n].m[2][2] = 变换矩阵.r[2].m128_f32[2];
                                }

                            for (u = 0; u < m动画数据->片段[i].动画层[k].物体[m].缩放.size(); u++)
                            {

                                //在帧区间内
                                if (u + 1 < m动画数据->片段[i].动画层[k].物体[m].缩放.size())
                                    if (m动画数据->片段[i].动画层[k].物体[m].缩放[u].帧数 <= j &&
                                        m动画数据->片段[i].动画层[k].物体[m].缩放[u + 1].帧数 > j)
                                    {
                                        l帧比例 = ((float)j - m动画数据->片段[i].动画层[k].物体[m].缩放[u].帧数) /
                                            (m动画数据->片段[i].动画层[k].物体[m].缩放[u + 1].帧数 -
                                                m动画数据->片段[i].动画层[k].物体[m].缩放[u].帧数);
                                        缩放.m128_f32[0] = (m动画数据->片段[i].动画层[k].物体[m].缩放[u + 1].缩放.x -
                                            m动画数据->片段[i].动画层[k].物体[m].缩放[u].缩放.x) * l帧比例 +
                                            m动画数据->片段[i].动画层[k].物体[m].缩放[u].缩放.x;
                                        缩放.m128_f32[1] = (m动画数据->片段[i].动画层[k].物体[m].缩放[u + 1].缩放.y -
                                            m动画数据->片段[i].动画层[k].物体[m].缩放[u].缩放.y) * l帧比例 +
                                            m动画数据->片段[i].动画层[k].物体[m].缩放[u].缩放.y;
                                        缩放.m128_f32[2] = (m动画数据->片段[i].动画层[k].物体[m].缩放[u + 1].缩放.z -
                                            m动画数据->片段[i].动画层[k].物体[m].缩放[u].缩放.z) * l帧比例 +
                                            m动画数据->片段[i].动画层[k].物体[m].缩放[u].缩放.z;

                                        变换矩阵 = XMMatrixScaling(缩放.m128_f32[1], 缩放.m128_f32[0], 缩放.m128_f32[2]);
                                        变换矩阵2 = XMLoadFloat4x3(&动画轨道[i].帧[j - 帧偏移].物体变换[n]);
                                        变换矩阵 *= 变换矩阵2;

                                        动画轨道[i].帧[j - 帧偏移].物体变换[n].m[0][0] = 变换矩阵.r[0].m128_f32[0];
                                        动画轨道[i].帧[j - 帧偏移].物体变换[n].m[0][1] = 变换矩阵.r[0].m128_f32[1];
                                        动画轨道[i].帧[j - 帧偏移].物体变换[n].m[0][2] = 变换矩阵.r[0].m128_f32[2];
                                        动画轨道[i].帧[j - 帧偏移].物体变换[n].m[1][0] = 变换矩阵.r[1].m128_f32[0];
                                        动画轨道[i].帧[j - 帧偏移].物体变换[n].m[1][1] = 变换矩阵.r[1].m128_f32[1];
                                        动画轨道[i].帧[j - 帧偏移].物体变换[n].m[1][2] = 变换矩阵.r[1].m128_f32[2];
                                        动画轨道[i].帧[j - 帧偏移].物体变换[n].m[2][0] = 变换矩阵.r[2].m128_f32[0];
                                        动画轨道[i].帧[j - 帧偏移].物体变换[n].m[2][1] = 变换矩阵.r[2].m128_f32[1];
                                        动画轨道[i].帧[j - 帧偏移].物体变换[n].m[2][2] = 变换矩阵.r[2].m128_f32[2];
                                    }
                            }

                            //在帧区间后
                            if (m动画数据->片段[i].动画层[k].物体[m].缩放.size() > 0)
                                if (m动画数据->片段[i].动画层[k].物体[m].缩放[m动画数据->片段[i].动画层[k].物体[m].缩放.size() - 1].帧数 <= j)
                                {
                                    缩放.m128_f32[0] = m动画数据->片段[i].动画层[k].物体[m].缩放[
                                        m动画数据->片段[i].动画层[k].物体[m].缩放.size() - 1].缩放.x;
                                    缩放.m128_f32[1] = m动画数据->片段[i].动画层[k].物体[m].缩放[
                                        m动画数据->片段[i].动画层[k].物体[m].缩放.size() - 1].缩放.y;
                                    缩放.m128_f32[2] = m动画数据->片段[i].动画层[k].物体[m].缩放[
                                        m动画数据->片段[i].动画层[k].物体[m].缩放.size() - 1].缩放.z;

                                    变换矩阵 = XMMatrixScaling(缩放.m128_f32[1], 缩放.m128_f32[0], 缩放.m128_f32[2]);
                                    变换矩阵2 = XMLoadFloat4x3(&动画轨道[i].帧[j - 帧偏移].物体变换[n]);
                                    变换矩阵 *= 变换矩阵2;

                                    动画轨道[i].帧[j - 帧偏移].物体变换[n].m[0][0] = 变换矩阵.r[0].m128_f32[0];
                                    动画轨道[i].帧[j - 帧偏移].物体变换[n].m[0][1] = 变换矩阵.r[0].m128_f32[1];
                                    动画轨道[i].帧[j - 帧偏移].物体变换[n].m[0][2] = 变换矩阵.r[0].m128_f32[2];
                                    动画轨道[i].帧[j - 帧偏移].物体变换[n].m[1][0] = 变换矩阵.r[1].m128_f32[0];
                                    动画轨道[i].帧[j - 帧偏移].物体变换[n].m[1][1] = 变换矩阵.r[1].m128_f32[1];
                                    动画轨道[i].帧[j - 帧偏移].物体变换[n].m[1][2] = 变换矩阵.r[1].m128_f32[2];
                                    动画轨道[i].帧[j - 帧偏移].物体变换[n].m[2][0] = 变换矩阵.r[2].m128_f32[0];
                                    动画轨道[i].帧[j - 帧偏移].物体变换[n].m[2][1] = 变换矩阵.r[2].m128_f32[1];
                                    动画轨道[i].帧[j - 帧偏移].物体变换[n].m[2][2] = 变换矩阵.r[2].m128_f32[2];
                                }
                        }
                    }

                    //加载骨骼变换
                    for (n = 1; n < 骨骼数量; n++)
                    {
                        if (m骨骼名称[n].compare(m动画数据->片段[i].动画层[k].物体[m].物体名称) == 0)
                        {
                            搜索骨骼树(m骨骼名称[n], 骨骼节点);

                            for (w = 0; w < m蒙皮数据->关联物体.size(); w++)
                            {
                                for (v = 0; v < m蒙皮数据->关联物体[w].骨骼.size(); v++)
                                {
                                    if (m蒙皮数据->关联物体[w].骨骼[v].骨骼名称 == m骨骼名称[n])
                                    {
                                        搜索骨骼树(m骨骼名称[n], 骨骼节点);
                                        XMStoreFloat3x3(&骨骼节点->初始骨骼旋转, m蒙皮数据->关联物体[w].骨骼[v].关联骨骼旋转矩阵);
                                        骨骼节点->初始骨骼位置.x = m蒙皮数据->关联物体[w].骨骼[v].关联骨骼旋转矩阵.r[3].m128_f32[0];
                                        骨骼节点->初始骨骼位置.y = m蒙皮数据->关联物体[w].骨骼[v].关联骨骼旋转矩阵.r[3].m128_f32[1];
                                        骨骼节点->初始骨骼位置.z = m蒙皮数据->关联物体[w].骨骼[v].关联骨骼旋转矩阵.r[3].m128_f32[2];
                                        goto 跳出5;
                                    }
                                }
                            }
                            跳出5: if (0);

                            //位置变换
                            if (m动画数据->片段[i].动画层[k].物体[m].位置.size() == 0)
                            {
                                是否为零矩阵 = true;
                                for (x = 0; x < 4; x++)
                                    for (y = 0; y < 4; y++)
                                        if (造型->绑定造型[m骨骼名称[n]].r[x].m128_f32[y] != 0.0f) 是否为零矩阵 = false;
                                if (是否为零矩阵)
                                {
                                    骨骼节点->动画轨道[i].帧[j - 帧偏移].变换.位置 = 骨骼节点->原始位置;
                                }
                                else
                                {
                                    骨骼节点->动画轨道[i].帧[j - 帧偏移].变换.位置.x = 造型->绑定造型[m骨骼名称[n]].r[3].m128_f32[0];
                                    骨骼节点->动画轨道[i].帧[j - 帧偏移].变换.位置.y = 造型->绑定造型[m骨骼名称[n]].r[3].m128_f32[1];
                                    骨骼节点->动画轨道[i].帧[j - 帧偏移].变换.位置.z = 造型->绑定造型[m骨骼名称[n]].r[3].m128_f32[2];
                                }

                            }

                            //在帧前或前帧上
                            if (m动画数据->片段[i].动画层[k].物体[m].位置.size() != 0)
                                if (m动画数据->片段[i].动画层[k].物体[m].位置[0].帧数 >= j)
                                {
                                    骨骼节点->动画轨道[i].帧[j - 帧偏移].变换.位置.z = m动画数据->片段[i].动画层[k].物体[m].位置[0].位置.x;
                                    骨骼节点->动画轨道[i].帧[j - 帧偏移].变换.位置.y = m动画数据->片段[i].动画层[k].物体[m].位置[0].位置.y;
                                    骨骼节点->动画轨道[i].帧[j - 帧偏移].变换.位置.x = -m动画数据->片段[i].动画层[k].物体[m].位置[0].位置.z;
                                }

                            for (u = 0; u < m动画数据->片段[i].动画层[k].物体[m].位置.size(); u++)
                            {
                                //在帧区间内
                                if (u + 1 < m动画数据->片段[i].动画层[k].物体[m].位置.size())
                                    if (m动画数据->片段[i].动画层[k].物体[m].位置[u].帧数 <= j &&
                                        m动画数据->片段[i].动画层[k].物体[m].位置[u + 1].帧数 > j)
                                    {
                                        l帧比例 = ((float)j - m动画数据->片段[i].动画层[k].物体[m].位置[u].帧数) /
                                            (m动画数据->片段[i].动画层[k].物体[m].位置[u + 1].帧数 -
                                                m动画数据->片段[i].动画层[k].物体[m].位置[u].帧数);

                                        骨骼节点->动画轨道[i].帧[j - 帧偏移].变换.位置.z = (m动画数据->片段[i].动画层[k].物体[m].位置[u + 1].位置.x -
                                            m动画数据->片段[i].动画层[k].物体[m].位置[u].位置.x) * l帧比例 +
                                            m动画数据->片段[i].动画层[k].物体[m].位置[u].位置.x;
                                        骨骼节点->动画轨道[i].帧[j - 帧偏移].变换.位置.y = (m动画数据->片段[i].动画层[k].物体[m].位置[u + 1].位置.y -
                                            m动画数据->片段[i].动画层[k].物体[m].位置[u].位置.y) * l帧比例 +
                                            m动画数据->片段[i].动画层[k].物体[m].位置[u].位置.y;
                                        骨骼节点->动画轨道[i].帧[j - 帧偏移].变换.位置.x = -((m动画数据->片段[i].动画层[k].物体[m].位置[u + 1].位置.z -
                                            m动画数据->片段[i].动画层[k].物体[m].位置[u].位置.z) * l帧比例 +
                                            m动画数据->片段[i].动画层[k].物体[m].位置[u].位置.z);
                                    }
                            }

                            //在帧区间后或后帧上
                            if (m动画数据->片段[i].动画层[k].物体[m].位置.size() > 0)
                                if (m动画数据->片段[i].动画层[k].物体[m].位置[m动画数据->片段[i].动画层[k].物体[m].位置.size() - 1].帧数 <= j)
                                {
                                    v = m动画数据->片段[i].动画层[k].物体[m].位置.size() - 1;
                                    骨骼节点->动画轨道[i].帧[j - 帧偏移].变换.位置.z = m动画数据->片段[i].动画层[k].物体[m].位置[v].位置.x;
                                    骨骼节点->动画轨道[i].帧[j - 帧偏移].变换.位置.y = m动画数据->片段[i].动画层[k].物体[m].位置[v].位置.y;
                                    骨骼节点->动画轨道[i].帧[j - 帧偏移].变换.位置.x = -m动画数据->片段[i].动画层[k].物体[m].位置[v].位置.z;
                                }

                            //旋转变换
                            if (m动画数据->片段[i].动画层[k].物体[m].旋转.size() == 0)
                            {
                                是否为零矩阵 = true;
                                for (x = 0; x < 4; x++)
                                    for (y = 0; y < 4; y++)
                                        if (造型->绑定造型[m骨骼名称[n]].r[x].m128_f32[y] != 0.0f) 是否为零矩阵 = false;
                                if (是否为零矩阵)
                                {
                                    骨骼节点->动画轨道[i].帧[j - 帧偏移].变换.旋转 = 骨骼节点->原始旋转;
                                    XMStoreFloat3x3(&骨骼节点->动画轨道[i].帧[j - 帧偏移].旋转, XMMatrixRotationRollPitchYaw(
                                        骨骼节点->原始旋转.x * XM_PI / 180, 骨骼节点->原始旋转.y * XM_PI / 180, 骨骼节点->原始旋转.z * XM_PI / 180));
                                }
                                else
                                {
                                    XMStoreFloat3x3(&骨骼节点->动画轨道[i].帧[j - 帧偏移].旋转, 造型->绑定造型[m骨骼名称[n]]);
                                } 
                            }

                            //在帧前或帧上
                            if (m动画数据->片段[i].动画层[k].物体[m].旋转.size() != 0)
                                if (m动画数据->片段[i].动画层[k].物体[m].旋转[0].帧数 >= j)
                                {
                                    骨骼节点->动画轨道[i].帧[j - 帧偏移].变换.旋转.x = m动画数据->片段[i].动画层[k].物体[m].旋转[0].旋转.y;
                                    骨骼节点->动画轨道[i].帧[j - 帧偏移].变换.旋转.y = m动画数据->片段[i].动画层[k].物体[m].旋转[0].旋转.z;
                                    骨骼节点->动画轨道[i].帧[j - 帧偏移].变换.旋转.z = m动画数据->片段[i].动画层[k].物体[m].旋转[0].旋转.x;
                                    XMStoreFloat3x3(&骨骼节点->动画轨道[i].帧[j - 帧偏移].旋转, XMMatrixRotationRollPitchYaw(
                                        m动画数据->片段[i].动画层[k].物体[m].旋转[0].旋转.y * XM_PI / 180,
                                        m动画数据->片段[i].动画层[k].物体[m].旋转[0].旋转.z * XM_PI / 180,
                                        m动画数据->片段[i].动画层[k].物体[m].旋转[0].旋转.x * XM_PI / 180));
                                }

                            //在帧区间内
                            for (u = 0; u < m动画数据->片段[i].动画层[k].物体[m].旋转.size(); u++)
                            {
                                if (u + 1 < m动画数据->片段[i].动画层[k].物体[m].旋转.size())
                                    if (m动画数据->片段[i].动画层[k].物体[m].旋转[u].帧数 <= j && m动画数据->片段[i].动画层[k].物体[m].旋转[u + 1].帧数 > j)
                                    {
                                        l帧比例 = ((float)j - m动画数据->片段[i].动画层[k].物体[m].旋转[u].帧数) /
                                            (m动画数据->片段[i].动画层[k].物体[m].旋转[u + 1].帧数 -
                                                m动画数据->片段[i].动画层[k].物体[m].旋转[u].帧数);

                                        l旋转向量.m128_f32[0] = m动画数据->片段[i].动画层[k].物体[m].旋转[u].旋转.x;
                                        l旋转向量.m128_f32[1] = m动画数据->片段[i].动画层[k].物体[m].旋转[u].旋转.y;
                                        l旋转向量.m128_f32[2] = m动画数据->片段[i].动画层[k].物体[m].旋转[u].旋转.z;
                                        l旋转向量2.m128_f32[0] = m动画数据->片段[i].动画层[k].物体[m].旋转[u + 1].旋转.x;
                                        l旋转向量2.m128_f32[1] = m动画数据->片段[i].动画层[k].物体[m].旋转[u + 1].旋转.y;
                                        l旋转向量2.m128_f32[2] = m动画数据->片段[i].动画层[k].物体[m].旋转[u + 1].旋转.z;

                                        l旋转向量 = (l旋转向量2 - l旋转向量) * l帧比例 + l旋转向量;

                                        骨骼节点->动画轨道[i].帧[j - 帧偏移].变换.旋转.z = l旋转向量.m128_f32[0];
                                        骨骼节点->动画轨道[i].帧[j - 帧偏移].变换.旋转.x = l旋转向量.m128_f32[1];
                                        骨骼节点->动画轨道[i].帧[j - 帧偏移].变换.旋转.y = l旋转向量.m128_f32[2];
                                        XMStoreFloat3x3(&骨骼节点->动画轨道[i].帧[j - 帧偏移].旋转, XMMatrixRotationRollPitchYaw(
                                            l旋转向量.m128_f32[1] * XM_PI / 180, l旋转向量.m128_f32[2] * XM_PI / 180,
                                            l旋转向量.m128_f32[0] * XM_PI / 180));
                                    }
                            }

                            //在帧区间后
                            if (m动画数据->片段[i].动画层[k].物体[m].旋转.size() > 0)
                                if (m动画数据->片段[i].动画层[k].物体[m].旋转[m动画数据->片段[i].动画层[k].物体[m].旋转.size() - 1].帧数 <= j)
                                {
                                    u = m动画数据->片段[i].动画层[k].物体[m].旋转.size() - 1;
                                    骨骼节点->动画轨道[i].帧[j - 帧偏移].变换.旋转.z = m动画数据->片段[i].动画层[k].物体[m].旋转[u].旋转.x;
                                    骨骼节点->动画轨道[i].帧[j - 帧偏移].变换.旋转.x = m动画数据->片段[i].动画层[k].物体[m].旋转[u].旋转.y;
                                    骨骼节点->动画轨道[i].帧[j - 帧偏移].变换.旋转.y = m动画数据->片段[i].动画层[k].物体[m].旋转[u].旋转.z;
                                    XMStoreFloat3x3(&骨骼节点->动画轨道[i].帧[j - 帧偏移].旋转, XMMatrixRotationRollPitchYaw(
                                        m动画数据->片段[i].动画层[k].物体[m].旋转[u].旋转.y * XM_PI / 180, 
                                        m动画数据->片段[i].动画层[k].物体[m].旋转[u].旋转.z * XM_PI / 180,
                                        m动画数据->片段[i].动画层[k].物体[m].旋转[u].旋转.x * XM_PI / 180));
                                }

                            //缩放变换
                            if (m动画数据->片段[i].动画层[k].物体[m].缩放.size() == 0)
                            {
                                骨骼节点->动画轨道[i].帧[j - 帧偏移].变换.缩放 = XMFLOAT3{ 1.0f, 1.0f, 1.0f };
                            }

                            //在帧前或前帧上
                            if (m动画数据->片段[i].动画层[k].物体[m].缩放.size() != 0)
                                if (m动画数据->片段[i].动画层[k].物体[m].缩放[m动画数据->片段[i].动画层[k].物体[m].缩放.size() - 1].帧数 >= j)
                                {
                                    骨骼节点->动画轨道[i].帧[j - 帧偏移].变换.缩放.z =
                                        m动画数据->片段[i].动画层[k].物体[m].缩放[0].缩放.x;
                                    骨骼节点->动画轨道[i].帧[j - 帧偏移].变换.缩放.x =
                                        m动画数据->片段[i].动画层[k].物体[m].缩放[0].缩放.y;
                                    骨骼节点->动画轨道[i].帧[j - 帧偏移].变换.缩放.y =
                                        m动画数据->片段[i].动画层[k].物体[m].缩放[0].缩放.z;
                                }

                            for (u = 0; u < m动画数据->片段[i].动画层[k].物体[m].缩放.size(); u++)
                            {
                                //在帧区间内
                                if (u + 1 < m动画数据->片段[i].动画层[k].物体[m].缩放.size())
                                    if (m动画数据->片段[i].动画层[k].物体[m].缩放[u].帧数 <= j &&
                                        m动画数据->片段[i].动画层[k].物体[m].缩放[u + 1].帧数 > j)
                                    {
                                        l帧比例 = ((float)j - m动画数据->片段[i].动画层[k].物体[m].缩放[u].帧数) /
                                            (m动画数据->片段[i].动画层[k].物体[m].缩放[u + 1].帧数 -
                                                m动画数据->片段[i].动画层[k].物体[m].缩放[u].帧数);
                                        骨骼节点->动画轨道[i].帧[j - 帧偏移].变换.缩放.z = (m动画数据->片段[i].动画层[k].物体[m].缩放[u + 1].缩放.x
                                            - m动画数据->片段[i].动画层[k].物体[m].缩放[u].缩放.x) * l帧比例 +
                                            m动画数据->片段[i].动画层[k].物体[m].缩放[u].缩放.x;
                                        骨骼节点->动画轨道[i].帧[j - 帧偏移].变换.缩放.x = (m动画数据->片段[i].动画层[k].物体[m].缩放[u + 1].缩放.y
                                            - m动画数据->片段[i].动画层[k].物体[m].缩放[u].缩放.y) * l帧比例 +
                                            m动画数据->片段[i].动画层[k].物体[m].缩放[u].缩放.y;
                                        骨骼节点->动画轨道[i].帧[j - 帧偏移].变换.缩放.y = (m动画数据->片段[i].动画层[k].物体[m].缩放[u + 1].缩放.z
                                            - m动画数据->片段[i].动画层[k].物体[m].缩放[u].缩放.z) * l帧比例 +
                                            m动画数据->片段[i].动画层[k].物体[m].缩放[u].缩放.z;
                                    }
                            }

                            //在帧区间后
                            if (m动画数据->片段[i].动画层[k].物体[m].缩放.size() > 0)
                                if (m动画数据->片段[i].动画层[k].物体[m].缩放[m动画数据->片段[i].动画层[k].物体[m].缩放.size() - 1].帧数 <= j)
                                {
                                    骨骼节点->动画轨道[i].帧[j - 帧偏移].变换.缩放.z =
                                        m动画数据->片段[i].动画层[k].物体[m].缩放[m动画数据->片段[i].动画层[k].物体[m].缩放.size() - 1].缩放.x;
                                    骨骼节点->动画轨道[i].帧[j - 帧偏移].变换.缩放.x =
                                        m动画数据->片段[i].动画层[k].物体[m].缩放[m动画数据->片段[i].动画层[k].物体[m].缩放.size() - 1].缩放.y;
                                    骨骼节点->动画轨道[i].帧[j - 帧偏移].变换.缩放.y =
                                        m动画数据->片段[i].动画层[k].物体[m].缩放[m动画数据->片段[i].动画层[k].物体[m].缩放.size() - 1].缩放.z;
                                }
                        }
                    }
                }
            }
        }
    }

}

void C动态物体::合并骨骼树(S变换节点* 变换节点)
{
    UINT i = 0;
    UINT j = 0;
    UINT k = 0;
    UINT m = 0;
    UINT n = 0;
    XMMATRIX 旋转变换{};
    XMMATRIX 旋转变换2{};
    XMMATRIX 旋转变换3{};
    XMMATRIX 旋转变换4{};
    XMMATRIX 旋转变换5{};
    XMMATRIX 预旋转 = XMMatrixIdentity();
    XMMATRIX 预旋转2 = XMMatrixIdentity();
    XMMATRIX 旋转变换测试{};
    XMMATRIX 初始旋转{};
    XMMATRIX 初始旋转2{};
    XMMATRIX 上一旋转{};
    XMMATRIX 上一旋转2{};
    XMMATRIX 上一旋转逆{};
    XMMATRIX 上一初始旋转{};
    XMMATRIX 世界矩阵{};
    XMMATRIX 最终变换{};
    XMMATRIX 最初变换 = XMMatrixIdentity();
    XMMATRIX 初始旋转偏移{};
    XMVECTOR 位置{};
    XMVECTOR 位置2{};
    XMVECTOR 位置偏移{};
    XMMATRIX 旋转修正 = XMMatrixIdentity();
    S变换节点* p变换节点 = nullptr;
    S变换节点* p变换节点2 = nullptr;
    XMMATRIX 骨骼偏移 = XMMatrixIdentity();
    bool 是否为零矩阵 = 0;
    int u = 0;
    int v = 0;

    for (j = 0; j < 动画轨道.size(); j++)
    {
        for (k = 0; k < 动画轨道[j].帧.size(); k++)
        {
            for (m = 0; m < 动画轨道[j].帧[k].骨骼变换.size(); m++)
            {
                if (m骨骼名称[m] == 变换节点->节点名称)
                {
                    最终变换 = XMMatrixIdentity();
                    预旋转 = XMMatrixIdentity();

                    p变换节点 = 变换节点;
                    while (p变换节点->父节点)
                    {
                        是否为零矩阵 = 1;
                        for (u = 0; u < 4; u++)
                            for (v = 0; v < 4; v++)
                                if (造型->绑定造型[p变换节点->节点名称].r[u].m128_f32[v] != 0.0f) 是否为零矩阵 = 0;
                        if (是否为零矩阵)
                        {
                            位置2 = XMVECTOR{ -p变换节点->初始骨骼位置.x, p变换节点->初始骨骼位置.y, -p变换节点->初始骨骼位置.z };
                            if (p变换节点->初始骨骼位置.x == 0.0f && p变换节点->初始骨骼位置.y == 0.0f && p变换节点->初始骨骼位置.z == 0.0f)
                            {
                                位置2.m128_f32[0] = p变换节点->原始位置.x;
                                位置2.m128_f32[1] = p变换节点->原始位置.y;
                                位置2.m128_f32[2] = p变换节点->原始位置.z;
                                位置2 = XMVector3TransformCoord(位置2, p变换节点->世界矩阵);
                                位置2.m128_f32[0] = 位置2.m128_f32[0] + p变换节点->父节点->变换.位置.x;
                                位置2.m128_f32[1] = 位置2.m128_f32[1] + p变换节点->父节点->变换.位置.y;
                                位置2.m128_f32[2] = 位置2.m128_f32[2] + p变换节点->父节点->变换.位置.z;
                            }
                            最终变换 *= XMMatrixTranslation(-位置2.m128_f32[0], -位置2.m128_f32[1], -位置2.m128_f32[2]);
                        }
                        else
                        {
                            位置 = XMVECTOR{ 造型->绑定造型[p变换节点->节点名称].r[3].m128_f32[0], 造型->绑定造型[p变换节点->节点名称].r[3].m128_f32[1],
                                造型->绑定造型[p变换节点->节点名称].r[3].m128_f32[2] };
                            最终变换 *= XMMatrixTranslation(-位置.m128_f32[0], -位置.m128_f32[1], -位置.m128_f32[2]);
                        }

                        float rx = p变换节点->动画轨道[j].帧[k].变换.旋转.x * XM_PI / 180;
                        float ry = p变换节点->动画轨道[j].帧[k].变换.旋转.y * XM_PI / 180;
                        float rz = p变换节点->动画轨道[j].帧[k].变换.旋转.z * XM_PI / 180;
                        旋转变换4 = XMMatrixRotationRollPitchYaw(rx, ry, rz);
                        p变换节点2 = p变换节点;
                        while (p变换节点2->父节点)
                        {
                            rx = p变换节点2->父节点->动画轨道[j].帧[k].变换.旋转.x * XM_PI / 180;
                            ry = p变换节点2->父节点->动画轨道[j].帧[k].变换.旋转.y * XM_PI / 180;
                            rz = p变换节点2->父节点->动画轨道[j].帧[k].变换.旋转.z * XM_PI / 180;
                            旋转变换4 *= XMMatrixRotationRollPitchYaw(rx, ry, rz);

                            p变换节点2 = p变换节点2->父节点;
                        }
                        旋转变换2 = 造型->绑定造型[p变换节点->节点名称];
                        是否为零矩阵 = 1;
                        for (u = 0; u < 4; u++)
                            for (v = 0; v < 4; v++)
                                if (旋转变换2.r[u].m128_f32[v] != 0.0f) 是否为零矩阵 = 0;
                        if (是否为零矩阵)
                        {
                            旋转变换2 = XMLoadFloat3x3(&p变换节点->初始骨骼旋转);
                            if (p变换节点->初始骨骼旋转.m[0][0] == 1.0f && p变换节点->初始骨骼旋转.m[1][1] == 1.0f &&
                                p变换节点->初始骨骼旋转.m[2][2] == 1.0f)
                            {
                                rx = p变换节点->动画轨道[j].帧[0].变换.旋转.x * XM_PI / 180;
                                ry = p变换节点->动画轨道[j].帧[0].变换.旋转.y * XM_PI / 180;
                                rz = p变换节点->动画轨道[j].帧[0].变换.旋转.z * XM_PI / 180;
                                旋转变换2 = XMMatrixRotationRollPitchYaw(rx, ry, rz);
                                p变换节点2 = p变换节点;
                                while (p变换节点2->父节点)
                                {
                                    rx = p变换节点2->父节点->动画轨道[j].帧[0].变换.旋转.x * XM_PI / 180;
                                    ry = p变换节点2->父节点->动画轨道[j].帧[0].变换.旋转.y * XM_PI / 180;
                                    rz = p变换节点2->父节点->动画轨道[j].帧[0].变换.旋转.z * XM_PI / 180;
                                    旋转变换2 *= XMMatrixRotationRollPitchYaw(rx, ry, rz);

                                    p变换节点2 = p变换节点2->父节点;
                                }
                            }
                        }
                        旋转变换2.r[3].m128_f32[0] = 0.0f; 旋转变换2.r[3].m128_f32[1] = 0.0f; 旋转变换2.r[3].m128_f32[2] = 0.0f;
                        旋转变换2 = XMMatrixInverse(0, 旋转变换2);

                        p变换节点2 = p变换节点;
                        rx = p变换节点2->父节点->动画轨道[j].帧[k].变换.旋转.x * XM_PI / 180;
                        ry = p变换节点2->父节点->动画轨道[j].帧[k].变换.旋转.y * XM_PI / 180;
                        rz = p变换节点2->父节点->动画轨道[j].帧[k].变换.旋转.z * XM_PI / 180;
                        旋转变换 = XMMatrixRotationRollPitchYaw(rx, ry, rz);
                        p变换节点2 = p变换节点->父节点;
                        while (p变换节点2->父节点)
                        {
                            rx = p变换节点2->父节点->动画轨道[j].帧[k].变换.旋转.x * XM_PI / 180;
                            ry = p变换节点2->父节点->动画轨道[j].帧[k].变换.旋转.y * XM_PI / 180;
                            rz = p变换节点2->父节点->动画轨道[j].帧[k].变换.旋转.z * XM_PI / 180;
                            旋转变换 *= XMMatrixRotationRollPitchYaw(rx, ry, rz);

                            p变换节点2 = p变换节点2->父节点;
                        }
                        旋转变换3 = 造型->绑定造型[p变换节点->父节点->节点名称];
                        是否为零矩阵 = 1;
                        for (u = 0; u < 4; u++)
                            for (v = 0; v < 4; v++)
                                if (旋转变换3.r[u].m128_f32[v] != 0.0f) 是否为零矩阵 = 0;
                        if (是否为零矩阵)
                        {
                            旋转变换3 = XMLoadFloat3x3(&p变换节点->父节点->初始骨骼旋转);
                            if (p变换节点->父节点->初始骨骼旋转.m[0][0] == 1.0f && p变换节点->父节点->初始骨骼旋转.m[1][1] == 1.0f &&
                                p变换节点->父节点->初始骨骼旋转.m[2][2] == 1.0f)
                            {
                                rx = p变换节点->父节点->动画轨道[j].帧[0].变换.旋转.x * XM_PI / 180;
                                ry = p变换节点->父节点->动画轨道[j].帧[0].变换.旋转.y * XM_PI / 180;
                                rz = p变换节点->父节点->动画轨道[j].帧[0].变换.旋转.z * XM_PI / 180;
                                旋转变换3 = XMMatrixRotationRollPitchYaw(rx, ry, rz);
                                p变换节点2 = p变换节点->父节点;
                                while (p变换节点2->父节点)
                                {
                                    rx = p变换节点2->父节点->动画轨道[j].帧[0].变换.旋转.x * XM_PI / 180;
                                    ry = p变换节点2->父节点->动画轨道[j].帧[0].变换.旋转.y * XM_PI / 180;
                                    rz = p变换节点2->父节点->动画轨道[j].帧[0].变换.旋转.z * XM_PI / 180;
                                    旋转变换3 *= XMMatrixRotationRollPitchYaw(rx, ry, rz);

                                    p变换节点2 = p变换节点2->父节点;
                                }
                            }
                        }
                        旋转变换3.r[3].m128_f32[0] = 0.0f; 旋转变换3.r[3].m128_f32[1] = 0.0f; 旋转变换3.r[3].m128_f32[2] = 0.0f;

                        旋转变换 = XMMatrixInverse(0, 旋转变换);

                        最终变换 = 最终变换 * 旋转变换2 * 旋转变换4 * 旋转变换 * 旋转变换3;

                        最终变换 *= XMMatrixTranslation(位置.m128_f32[0], 位置.m128_f32[1], 位置.m128_f32[2]);

                        预旋转 *= 轴和限制[p变换节点->节点名称].预旋转;
                        if (p变换节点->父节点->节点名称 == L"根节点")
                        {
                            预旋转2 = XMMatrixRotationAxis(XMVECTOR{ 0.0f, 0.0f, 1.0f, 0.0f }, XM_PI / 2);
                            最终变换 *= 预旋转 * 预旋转2;
                        }

                        p变换节点 = p变换节点->父节点;
                    }

                    //p变换节点 = 变换节点;

                    //while (p变换节点->父节点)
                    //{
                    //    if (p变换节点->父节点->节点名称 == L"根节点") break;
                    //    p变换节点 = p变换节点->父节点;
                    //}

                    //最终变换 *= XMMatrixTranslation(p变换节点->动画轨道[j].帧[k].变换.位置.x - 造型->绑定造型[p变换节点->节点名称].r[3].m128_f32[0],
                    //    p变换节点->动画轨道[j].帧[k].变换.位置.y - 造型->绑定造型[p变换节点->节点名称].r[3].m128_f32[1],
                    //    p变换节点->动画轨道[j].帧[k].变换.位置.z - 造型->绑定造型[p变换节点->节点名称].r[3].m128_f32[2]);

                    XMStoreFloat4x3(&动画轨道[j].帧[k].骨骼变换[m], 最终变换);

                }
            }
        }
    }

    for (i = 0; i < 变换节点->子节点数量; i++)
    {
        合并骨骼树(&变换节点->子节点[i]);
    }
}

void C动态物体::更新时间(float 时间变化)
{
    for (UINT i = 0; i < 动画轨道.size(); i++)
    {
        动画轨道[i].当前时间 += 时间变化 * 动画轨道[i].速度;
        动画轨道[i].是否结束 = 1;
        if (动画轨道[i].当前时间 >= 动画轨道[i].原始时长)
        {
            if (动画轨道[i].是否循环)
                动画轨道[i].当前时间 = 0;
            else
                动画轨道[i].当前时间 = 动画轨道[i].原始时长 - 0.001;
        }

        动画轨道[i].帧位 = 动画轨道[i].当前时间 / 动画轨道[i].原始时长 * (动画轨道[i].帧.size() - 1);
    }
}

XMMATRIX C动态物体::获取当前物体变换(UINT 属性)
{
    UINT 帧数 = 0;
    float 小数 = 0;
    XMMATRIX {};
    XMVECTOR 旋转x{};
    XMVECTOR 旋转y{};
    XMVECTOR 旋转z{};
    XMVECTOR 旋转x2{};
    XMVECTOR 旋转y2{};
    XMVECTOR 旋转z2{};
    XMVECTOR 位置{};
    XMVECTOR 位置2{};

    帧数 = (int)动画轨道[当前轨道].帧位;
    小数 = 动画轨道[当前轨道].帧位 - 帧数;

    s物体变换 = XMLoadFloat4x3(&动画轨道[当前轨道].帧[帧数].物体变换[属性]);

    位置 = XMVECTOR{ 动画轨道[当前轨道].帧[帧数].物体变换[属性].m[3][0], 动画轨道[当前轨道].帧[帧数].物体变换[属性].m[3][1],
        动画轨道[当前轨道].帧[帧数].物体变换[属性].m[3][2] };
    位置2 = XMVECTOR{ 动画轨道[当前轨道].帧[帧数 + 1].物体变换[属性].m[3][0], 动画轨道[当前轨道].帧[帧数 + 1].物体变换[属性].m[3][1],
        动画轨道[当前轨道].帧[帧数 + 1].物体变换[属性].m[3][2] };
    旋转x = XMVECTOR{ 动画轨道[当前轨道].帧[帧数].物体变换[属性].m[0][0], 动画轨道[当前轨道].帧[帧数].物体变换[属性].m[0][1],
        动画轨道[当前轨道].帧[帧数].物体变换[属性].m[0][2], 0.0f };
    旋转y = XMVECTOR{ 动画轨道[当前轨道].帧[帧数].物体变换[属性].m[1][0], 动画轨道[当前轨道].帧[帧数].物体变换[属性].m[1][1],
        动画轨道[当前轨道].帧[帧数].物体变换[属性].m[1][2], 0.0f };
    旋转z = XMVECTOR{ 动画轨道[当前轨道].帧[帧数].物体变换[属性].m[2][0], 动画轨道[当前轨道].帧[帧数].物体变换[属性].m[2][1],
        动画轨道[当前轨道].帧[帧数].物体变换[属性].m[2][2], 0.0f };
    旋转x2 = XMVECTOR{ 动画轨道[当前轨道].帧[帧数 + 1].物体变换[属性].m[0][0], 动画轨道[当前轨道].帧[帧数 + 1].物体变换[属性].m[0][1],
        动画轨道[当前轨道].帧[帧数 + 1].物体变换[属性].m[0][2], 0.0f };
    旋转y2 = XMVECTOR{ 动画轨道[当前轨道].帧[帧数 + 1].物体变换[属性].m[1][0], 动画轨道[当前轨道].帧[帧数 + 1].物体变换[属性].m[1][1],
        动画轨道[当前轨道].帧[帧数 + 1].物体变换[属性].m[1][2], 0.0f };
    旋转z2 = XMVECTOR{ 动画轨道[当前轨道].帧[帧数 + 1].物体变换[属性].m[2][0], 动画轨道[当前轨道].帧[帧数 + 1].物体变换[属性].m[2][1],
        动画轨道[当前轨道].帧[帧数 + 1].物体变换[属性].m[2][2], 0.0f };

    位置 = 位置 * (1 - 小数) + 位置2 * 小数;
    旋转x = 旋转x * (1 - 小数) + 旋转x2 * 小数;
    旋转y = 旋转y * (1 - 小数) + 旋转y2 * 小数;
    旋转z = 旋转z * (1 - 小数) + 旋转z2 * 小数;

    s物体变换.r[0].m128_f32[0] = 旋转x.m128_f32[0]; s物体变换.r[0].m128_f32[1] = 旋转x.m128_f32[1]; s物体变换.r[0].m128_f32[2] = 旋转x.m128_f32[2];
    s物体变换.r[1].m128_f32[0] = 旋转y.m128_f32[0]; s物体变换.r[1].m128_f32[1] = 旋转y.m128_f32[1]; s物体变换.r[1].m128_f32[2] = 旋转y.m128_f32[2];
    s物体变换.r[2].m128_f32[0] = 旋转z.m128_f32[0]; s物体变换.r[2].m128_f32[1] = 旋转z.m128_f32[1]; s物体变换.r[2].m128_f32[2] = 旋转z.m128_f32[2];
    s物体变换.r[3].m128_f32[0] = 位置.m128_f32[0]; s物体变换.r[3].m128_f32[1] = 位置.m128_f32[1]; s物体变换.r[3].m128_f32[2] = 位置.m128_f32[2];

    return s物体变换;
}

XMMATRIX* C动态物体::获取当前骨骼变换()
{
    UINT l帧数 = 0;
    float l小数 = 0;
    XMVECTOR l缩放{};
    XMMATRIX l初始旋转{};
    XMVECTOR 骨骼位置{};
    XMMATRIX l最终变换{};
    XMMATRIX l物体变换{};
    XMVECTOR 旋转x{};
    XMVECTOR 旋转y{};
    XMVECTOR 旋转z{};
    XMVECTOR 旋转x2{};
    XMVECTOR 旋转y2{};
    XMVECTOR 旋转z2{};
    XMVECTOR 位置{};
    XMVECTOR 位置2{};
    XMMATRIX 旋转 = XMMatrixIdentity();

    l帧数 = (int)动画轨道[当前轨道].帧位;
    l小数 = 动画轨道[当前轨道].帧位 - l帧数;

    for (UINT i = 1; i < 骨骼数量; i++)
    {
        l最终变换 = XMLoadFloat4x3(&动画轨道[当前轨道].帧[l帧数].骨骼变换[i]);
        位置 = XMVECTOR{ 动画轨道[当前轨道].帧[l帧数].骨骼变换[i].m[3][0], 动画轨道[当前轨道].帧[l帧数].骨骼变换[i].m[3][1],
            动画轨道[当前轨道].帧[l帧数].骨骼变换[i].m[3][2] };
        位置2 = XMVECTOR{ 动画轨道[当前轨道].帧[l帧数 + 1].骨骼变换[i].m[3][0], 动画轨道[当前轨道].帧[l帧数 + 1].骨骼变换[i].m[3][1],
            动画轨道[当前轨道].帧[l帧数 + 1].骨骼变换[i].m[3][2] };
        旋转x = XMVECTOR{ 动画轨道[当前轨道].帧[l帧数].骨骼变换[i].m[0][0], 动画轨道[当前轨道].帧[l帧数].骨骼变换[i].m[0][1],
            动画轨道[当前轨道].帧[l帧数].骨骼变换[i].m[0][2], 0.0f };
        旋转y = XMVECTOR{ 动画轨道[当前轨道].帧[l帧数].骨骼变换[i].m[1][0], 动画轨道[当前轨道].帧[l帧数].骨骼变换[i].m[1][1],
            动画轨道[当前轨道].帧[l帧数].骨骼变换[i].m[1][2], 0.0f };
        旋转z = XMVECTOR{ 动画轨道[当前轨道].帧[l帧数].骨骼变换[i].m[2][0], 动画轨道[当前轨道].帧[l帧数].骨骼变换[i].m[2][1],
            动画轨道[当前轨道].帧[l帧数].骨骼变换[i].m[2][2], 0.0f };
        旋转x2 = XMVECTOR{ 动画轨道[当前轨道].帧[l帧数 + 1].骨骼变换[i].m[0][0], 动画轨道[当前轨道].帧[l帧数 + 1].骨骼变换[i].m[0][1],
            动画轨道[当前轨道].帧[l帧数 + 1].骨骼变换[i].m[0][2], 0.0f };
        旋转y2 = XMVECTOR{ 动画轨道[当前轨道].帧[l帧数 + 1].骨骼变换[i].m[1][0], 动画轨道[当前轨道].帧[l帧数 + 1].骨骼变换[i].m[1][1],
            动画轨道[当前轨道].帧[l帧数 + 1].骨骼变换[i].m[1][2], 0.0f };
        旋转z2 = XMVECTOR{ 动画轨道[当前轨道].帧[l帧数 + 1].骨骼变换[i].m[2][0], 动画轨道[当前轨道].帧[l帧数 + 1].骨骼变换[i].m[2][1],
            动画轨道[当前轨道].帧[l帧数 + 1].骨骼变换[i].m[2][2], 0.0f };
        位置 = 位置 * (1 - l小数) + 位置2 * l小数;
        旋转x = 旋转x * (1 - l小数) + 旋转x2 * l小数;
        旋转y = 旋转y * (1 - l小数) + 旋转y2 * l小数;
        旋转z = 旋转z * (1 - l小数) + 旋转z2 * l小数;
        l最终变换.r[0].m128_f32[0] = 旋转x.m128_f32[0]; l最终变换.r[0].m128_f32[1] = 旋转x.m128_f32[1]; l最终变换.r[0].m128_f32[2] = 旋转x.m128_f32[2];
        l最终变换.r[1].m128_f32[0] = 旋转y.m128_f32[0]; l最终变换.r[1].m128_f32[1] = 旋转y.m128_f32[1]; l最终变换.r[1].m128_f32[2] = 旋转y.m128_f32[2];
        l最终变换.r[2].m128_f32[0] = 旋转z.m128_f32[0]; l最终变换.r[2].m128_f32[1] = 旋转z.m128_f32[1]; l最终变换.r[2].m128_f32[2] = 旋转z.m128_f32[2];
        l最终变换.r[3].m128_f32[0] = 位置.m128_f32[0]; l最终变换.r[3].m128_f32[1] = 位置.m128_f32[1]; l最终变换.r[3].m128_f32[2] = 位置.m128_f32[2];

        s骨骼变换[i] = l最终变换;
    }

    return s骨骼变换;
}

void C动态物体::设定动画速度(UINT 轨道, float 速度倍数)
{
    动画轨道[轨道].速度 = 速度倍数;
}

void C动态物体::设定动画轨道(UINT 轨道)
{
    当前轨道 = 轨道;
}

void C动态物体::设定轨道帧位置(UINT 轨道, float 百分比)
{
    动画轨道[轨道].当前时间 = 动画轨道[轨道].原始时长 * 百分比;
}

void C动态物体::设定播放模式(UINT 轨道, bool 是否循环)
{
    动画轨道[轨道].是否循环 = 是否循环;
}

bool C动态物体::检测动画结束(UINT 轨道)
{
    if (动画轨道[轨道].是否结束) return 1;
    else return 0;
}

void C动态物体::设置网格优化信息(float 法向量合并最大角度, float 贴图顶点采样最大间隔)
{
    this->法向量合并最大角度 = 法向量合并最大角度;
    this->贴图顶点采样最大间隔 = 贴图顶点采样最大间隔;
}

void C动态物体::释放合并顶点索引集()
{
    m合并索引集.clear();
    m合并索引集.shrink_to_fit();
}

void C动态物体::释放上传堆()
{
}

void C动态物体::绘制网格(UINT 属性)
{
    命令队列->IASetVertexBuffers(0, 1, &vbv);
    命令队列->IASetIndexBuffer(&ibv);
    命令队列->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    命令队列->DrawIndexedInstanced(this->属性->元素[属性]->索引数量, 1, this->属性->元素[属性]->起始索引, 0, 0);
}

void C动态物体::释放合并信息()
{
    delete m蒙皮数据; m蒙皮数据 = nullptr;
    delete m动画数据; m动画数据 = nullptr;
    //delete m根节点; m根节点 = nullptr;
    delete 造型; 造型 = nullptr;
    m优化顶点集.clear();
    m优化顶点集.shrink_to_fit();
    轴和限制.clear();
}

C动态物体::~C动态物体()
{
    delete 属性; 属性 = nullptr;
    delete[] s骨骼变换; s骨骼变换 = nullptr;
    delete s备用资料; s备用资料 = nullptr;
    if (顶点集) delete[] 顶点集; 顶点集 = nullptr;
    m骨骼名称.clear();
    m骨骼名称.shrink_to_fit();
    delete m根节点; m根节点 = nullptr;
}
