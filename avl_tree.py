# 참조 : https://www.geeksforgeeks.org/avl-tree-set-1-insertion/ 

class TreeNode(object):
  def __init__(self,val):
    self.val = val
    self.left = None
    self.right = None
    self.height = 1

class AVL_tree(object):
  def insert(self, root, key):
    if not root:
      return TreeNode(key)
    if key < root.val:
      root.left = self.insert(root.left, key)
    else:
      root.right = self.insert(root.right, key)
  
    root.height = 1 + max(self.getHeight(root.left), self.getHeight(root.right))

    balance = self.getBalance(root)
    if balance > 1 and key < root.left.val:
      return self.rightRotate(root)
    if balance > 1 and key > root.left.val:
      root.left = self.leftRotate(root.left)
      return self.rightRotate(root)
    if balance < -1 and key < root.right.val:
      root.right = self.rightRotate(root.right)
      return self.leftRotate(root)
    if balance < -1 and key > root.right.val:
      return self.leftRotate(root)
    return root
  def getHeight(self, root):
    if not root:
      return 0
    return root.height
  def getBalance(self, root):
    if not root: 
      return 0
    return self.getHeight(root.left) - self.getHeight(root.right)
  def leftRotate(self, z):
    y = z.right
    x = y.left
    z.right = x
    y.left = z
    z.height = 1 + max(self.getHeight(z.left), self.getHeight(z.right))
    y.height = 1 + max(self.getHeight(y.left), self.getHeight(y.right))

    return y

  def rightRotate(self, z):
    y = z.left
    x = y.right
    z.left = x
    y.right = z

    z.height = 1 + max(self.getHeight(z.left), self.getHeight(z.right))
    y.height = 1 + max(self.getHeight(y.left), self.getHeight(y.right))

    return y

  def preOrder(self, root):
    if not root:
      return
    print("{0} ".format(root.val),end = "")
    self.preOrder(root.left)
    self.preOrder(root.right)
  def postOrder(self, root):
    if not root:
      return
    self.postOrder(root.left)
    self.postOrder(root.right)
    print("{0} ".format(root.val),end = "")
    
myTree = AVL_tree()

root = None

root = myTree.insert(root, 10) #first the root would be TreeNode(10)
root = myTree.insert(root, 20)
root = myTree.insert(root, 30)
root = myTree.insert(root, 40)
root = myTree.insert(root, 50)
root = myTree.insert(root, 25)

print("Preorder traversal of the", 
      "constructed AVL tree is") 
myTree.preOrder(root)
print() 
myTree.postOrder(root) 
print()
