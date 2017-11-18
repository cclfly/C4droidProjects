# 找最小(十进制+二进制+八进制)回文数
num = 11
while true
	if num.to_s == num.to_s.reverse &&
		 num.to_s(2) == num.to_s(2).reverse &&
		 num.to_s(8) == num.to_s(8).reverse
		puts num
		break
	end
	# 只需要找奇数
	num += 2
end
