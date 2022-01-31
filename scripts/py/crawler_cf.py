import urllib.request
import bs4
import datetime
from bs4 import BeautifulSoup

data_dict = {
    'Title': '**EMPTY**',
    'Source': '**EMPTY**',
    'Problem Description': '**EMPTY**',
    'Input': '**EMPTY**',
    'Output': '**EMPTY**',
    'Example': '**EMPTY**',
    'Note': '**EMPTY**',
}

def mathProcess(s):
    s = s.replace("$$$", "$")
    s = s.replace("\le ", "\leqslant ").replace("\ge ", "\geqslant")
    return s



def divTextProcess(div):
    strBuffer = ''
    # 遍历处理每个<p>标签

    for each in div.find_all("p"):
        if strBuffer != '':
            strBuffer += '\n\n'
        for content in each.contents:
            # 处理
            if (type(content) != bs4.element.Tag):
                # 如果是文本，添加至字符串buffer中
                strBuffer += mathProcess(content.replace("       ", " "))
                # 如果不是第一个，加换行符
            else:
                tp = content.attrs['class'][0]
                if tp == 'tex-font-style-bf':
                    strBuffer += '**' + mathProcess(content.contents[0].replace("       ", " ")) + '**'
                elif tp == 'tex-graphics':
                    strBuffer += f"![]({content.attrs['src']})"


    return strBuffer

def getCodeForces(problemSet: str, problemId: str):
    # 题目链接
    url = f"https://codeforces.com/problemset/problem/{problemSet}/{problemId}"
    # 获取网页内容
    html = urllib.request.urlopen(url).read()
    # 格式化
    soup = BeautifulSoup(html, 'lxml')

    # 找到主体内容
    mainContent = soup.find_all(name="div", attrs={"class": "problem-statement"})[0]

    # Limit
    # 找到题目标题、时间、和内存限制
    # Title
    data_dict['Title'] = f"CodeForces {problemSet} " + mainContent.find_all(
        name="div", attrs={"class": "title"})[0].contents[-1]
    # Time Limit
    data_dict['Time Limit'] = mainContent.find_all(
        name="div", attrs={"class": "time-limit"})[0].contents[-1]
    # Memory Limit
    data_dict['Memory Limit'] = mainContent.find_all(
        name="div", attrs={"class": "memory-limit"})[0].contents[-1]


    # 处理题目描述
    data_dict['Problem Description'] = divTextProcess(mainContent.find_all("div")[10])

    div = mainContent.find_all(
        name="div", attrs={"class": "input-specification"})[0]
    data_dict['Input'] = divTextProcess(div)

    div = mainContent.find_all(
        name="div", attrs={"class": "output-specification"})[0]
    data_dict['Output'] = divTextProcess(div)

    # # Input
    # div = mainContent.find_all(name="div", attrs={"class": "input"})[0]
    # data_dict['Sample Input'] = "```cpp" + \
    #     div.find_all("pre")[0].contents[0] + '```'
    # # Onput
    # div = mainContent.find_all(name="div", attrs={"class": "output"})[0]
    # data_dict['Sample Onput'] = "```cpp" + \
    #     div.find_all("pre")[0].contents[0] + '```'

    inputs = []
    outs = []
    div = mainContent.find_all(name="div", attrs={"class": "input"})
    for i in div:
        inputs.append(i.find_all("pre")[0].contents[0])

    div = mainContent.find_all(name="div", attrs={"class": "output"})
    for i in div:
        outs.append(i.find_all("pre")[0].contents[0])

    data_dict['Example'] = [inputs, outs]


    if(len(mainContent.find_all(name="div", attrs={"class": "note"})) > 0):
        div = mainContent.find_all(name="div", attrs={"class": "note"})[0]
        data_dict['Note'] = divTextProcess(div)


    data_dict['Source'] = '[' + data_dict['Title'] + ']' + '(' + url + ')'
    return data_dict


def CodeForcesToMD(dict):
    ans = f"# {dict['Title']}\n\n"
    ans += f"## 题目描述\n\n{dict['Problem Description']}\n\n"
    ans += f"## 输入\n\n{dict['Input']}\n\n"
    ans += f"## 输出\n\n{dict['Output']}\n\n"
    ans += f"## 样例\n\n"
    for i in range(0, len(dict['Example'][0])):
        ans += f"#### 样例输入 #{i+1}\n\n```{dict['Example'][0][i]}```\n\n"
        ans += f"#### 样例输出 #{i+1}\n\n```{dict['Example'][1][i]}```\n\n"
    ans += f"## Note\n\n{dict['Note']}\n\n"
    ans += f"## Source\n\n{dict['Source']}\n\n"
    ans += f"Date: {datetime.datetime.now()}"
        
    return ans
