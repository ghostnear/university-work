#
#   Service. Not required to write specifications if variables are named right.
#

def addProduct(productList: list, name: str, quantity: int, price: int) -> dict:
    product = dict()
    product["name"] = name
    product["quantity"] = quantity
    product["price"] = price
    productList.append(product)

def getPrice(product: dict) -> int:
    return product["price"]

def getQuantity(product: dict) -> int:
    return product["quantity"]

def sortByQuantity(productList: list) -> None:
    productList.sort(key = getQuantity)

def sortByPrice(productList: list) -> None:
    productList.sort(key = getPrice)

def removeLessThanPrice(productList: list, price: int) -> None:
    for product in productList.copy():
        if getPrice(product) < price:
            productList.remove(product)

def removeMoreThanPrice(productList: list, price: int) -> None:
    for product in productList.copy():
        if getPrice(product) > price:
            productList.remove(product)

def test_functionalities() -> None:
    products = []
    addProduct(products, "test1", 3, 3)
    addProduct(products, "test2", 2, 2)
    assert len(products) == 2, "Product adding did not work right!"

    removeLessThanPrice(products, 3)
    assert len(products) == 1, "Product removing less than price did not work right!"

    addProduct(products, "test3", 4, 4)
    removeMoreThanPrice(products, 3)
    assert len(products) == 1, "Product removing more than price did not work right!"

    removeLessThanPrice(products, 10)
    assert len(products) == 0, "Removing all products by less than price did not work right!"

    print("\nAll tests passed successfully!\n")

if __name__ == "__main__":
    test_functionalities()