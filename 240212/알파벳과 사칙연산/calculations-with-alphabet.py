# 계산식을 구함
exp = input()

# 한 글자씩 쪼개줌
exp_divide = list(exp)

# 사용하는 알파벳들을 구함
alphas = list(set(filter(lambda x: x not in ["+" , "-", "*"], exp_divide)))

# 정렬
alphas.sort()

# 가장큰 결과를 반환하는 함수
def get_max_result():
    max_result =  - (2 ** 31)

    # 각 위치에 넣어줄 숫자들을 담고있는 리스트 
    nums_list = []

    def make_nums(nums = [], l = 0):
        if l == len(alphas):
            nums_list.append(nums)
            return

        for i in range(1, 5):
            make_nums(nums + [i], l + 1)

    make_nums()
    
    # 결과를 구하는 부분함수
    def get_result(nums):

        # 나누어준 연산식을 가져옴
        _exp_divide = exp_divide[:]

        # 받아온 nums를 바탕으로 각 알파벳에 숫자를 대치해줌
        alpha_dict = {}
        for alpha, num in zip(alphas, nums):
            alpha_dict[alpha] = num
        
        # 각 알파벳들을 숫자로 치환해줌
        for i, v in enumerate(_exp_divide):
            if v in alpha_dict:
                _exp_divide[i] = alpha_dict[v]

        # 세자리씩 받아와서 연산하고 결과와 나머지 연산들을 붙여서 다시 넣어줌 요소가 1개만 남을 때 까지 반복
        while len(_exp_divide) != 1:
            _result = 0
            num1, op, num2 = _exp_divide[0:3]

            if op == "+":
                _result = num1 + num2
            elif op == "-":
                _result = num1 - num2
            elif op == "*":
                _result = num1 * num2
            
            _exp_divide = [_result] + _exp_divide[3:]

        return _exp_divide[0]

    for nums in nums_list:
        max_result = max(max_result, get_result(nums))


    return max_result

print(get_max_result())