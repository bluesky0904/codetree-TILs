n, m, c = map(int, input().split())

# 입력된격자
input_grid = [
    list(map(int, input().split()))
    for _ in range(n)
]

# 도둑질하는 경우
steel_list = []

# 비트 만들기
def gen_bit_list(n):
    bit_list = []
    bit = [0] * n
    while bit[0] != 2:
        bit_list.append(bit[:])
        bit[n-1] += 1
        for i in range(n-1, 0, -1):
            if bit[i] == 2:
                bit[i] = 0
                bit[i - 1] += 1
    return bit_list

# 비트로 필터링하는 부분
def bit_filter(bitmask, original_list):
    filtered_list = []
    for i in range(len(bitmask)):
        if bitmask[i]:
            filtered_list.append(original_list[i])
    
    return filtered_list

# 가치구하기
def part_to_worth(part):
    return sum(map(lambda x: x * x, part))

# 반복문으로 도둑질하는 경우를 넣어주기
for row in range(n):
    for col in range(n - m + 1):
        end = col + m
        part = input_grid[row][col:end]
        
        # 필터링의 기준이 되는 비트를 구함
        bit_list = gen_bit_list(len(part))

        # 비트로 필터링을 하고 무게를 계산하여 넣어주는 부분
        for bit in bit_list:
            filtered_part = bit_filter(bit, part)

            if not len(filtered_part):
                continue
            
            w = sum(filtered_part)

            if w <= c:
                steel = (row, col, end, part_to_worth(filtered_part))
                steel_list.append(steel)

        if end == n:
            break

# 길이
l = len(steel_list)

# 최대 가치를 저장
max_sum_worth = 0

# 집합 자료형을 사용해서 겹침을 검사해서 가치를 만들구하고 최대가치를 비교해서 넣어줌
for i in range(l):
    steel_1 = steel_list[i]
    for j in range(i, l):
        steel_2 = steel_list[j]
        if steel_1[0] == steel_2[0]:
            set1 = set(range(steel_1[1], steel_1[2]))
            set2 = set(range(steel_2[1], steel_2[2]))

            if len(set1 - set2) != len(set1):
                continue
        
        sum_worth = steel_1[3] + steel_2[3]
        max_sum_worth = max(max_sum_worth, sum_worth)

print(max_sum_worth)