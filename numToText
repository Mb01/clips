def numToText( i ):
    """number to text up to 999"""
    numbers = ["Zero", "One","Two","Three","Four","Five","Six", "Seven", "Eight","Nine","Ten"]
    teens = ["Ten", "Eleven","Twelve","Thirteen","Fourteen","Fifteen","Sixteen","Seventeen","Eighteen","Nineteen"]
    special = [None, None, "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty","Ninety"]

    res = ""
    
    hundreds = (i%1000 -  i%100) / 100
    tens = (i%100 - i%10) / 10
    ones = i%10
    
    if hundreds:
        res += numbers[hundreds] + "Hundred"
    #Teens
    if tens == 1:
        res += teens[ones]
    elif tens > 0:
        res+= special[tens] 
    
    if tens != 1 and ones:
        res += numbers[ones]
   
    return res

def textDollar( i ):    
    millions = (i - i%1000000) / 1000000
    thousands = (i%1000000 - i%1000) / 1000
    hundreds = (i%1000) # and below
    
    res = ""
    
    if millions:
        res += numToText( millions ) + "Million"
    if thousands:
        res += numToText( thousands ) + "Thousand"
    if hundreds:
        res += numToText( hundreds )
    
    res += "Dollars"
    return res
