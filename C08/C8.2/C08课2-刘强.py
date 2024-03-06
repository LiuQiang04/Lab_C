import re


def count_characters(file_path):
    # count字典,key为字符,value为出现次数
    count = {}

    with open(file_path, 'r',encoding='utf-8') as f:
        count['\\n'] = 0
        for line in f:
            characters = re.findall(r'[\u4e00-\u9fa5。？！，、；：”“】【（）——……·~-《》/‘’| ]', line)
            for char in characters:
                count[char] = count.get(char, 0) + 1
            count['\\n'] += 1

    return count


result = count_characters('三国演义.txt')

with open('《三国演义》权重.txt', 'w', encoding='utf-8') as f:
    for char, n in result.items():
        f.write(f'{char}:{n}\n')    # 写入新生成的txt中

