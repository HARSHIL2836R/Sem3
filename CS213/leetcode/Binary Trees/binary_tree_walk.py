class TreeNode:  
    def __init__(self, value):  
        self.value = value  
        self.left = None  
        self.right = None

def pre_order_iterative(root):  
    if not root:  
        return []  
    
    stack = [root]  
    result = []  
    
    while stack:  
        node = stack.pop()  
        result.append(node.value)  
        # Push right first so left is processed next  
        if node.right:  
            stack.append(node.right)  
        if node.left:  
            stack.append(node.left)  
    return result

def in_order_iterative(root):  
    stack = []  
    result = []  
    current = root  
    
    while stack or current:  
        while current:  
            stack.append(current)  
            current = current.left  
        current = stack.pop()  
        result.append(current.value)  
        current = current.right  
    return result

def post_order_iterative(root):  
    if not root:  
        return []  
    
    stack = [root]  
    result = []  
    
    while stack:  
        node = stack.pop()  
        result.append(node.value)  
        if node.left:  
            stack.append(node.left)  
        if node.right:  
            stack.append(node.right)  
    
    return result[::-1]  # Reverse the result for correct post-order

def morris_in_order(root):  
    result = []  
    current = root  

    while current:  
        if not current.left:  # If there is no left child  
            result.append(current.value)  
            current = current.right  # Go to right child  
        else:  
            # Find the inorder predecessor  
            predecessor = current.left  
            while predecessor.right and predecessor.right != current:  
                predecessor = predecessor.right  
            
            if not predecessor.right:  # Make current as right child of its predecessor  
                predecessor.right = current  
                current = current.left  
            else:  # Revert the changes to restore the original tree  
                predecessor.right = None  
                result.append(current.value)  
                current = current.right  

    return result

def morris_pre_order(root):  
    result = []  
    current = root  

    while current:  
        if not current.left:  # If there is no left child  
            result.append(current.value)  
            current = current.right  # Go to right child  
        else:  
            # Find the inorder predecessor  
            predecessor = current.left  
            while predecessor.right and predecessor.right != current:  
                predecessor = predecessor.right  

            if not predecessor.right:  # Make current as right child of its predecessor  
                result.append(current.value)  # Visit the node  
                predecessor.right = current  
                current = current.left  
            else:  # Revert the changes to restore the original tree  
                predecessor.right = None  
                current = current.right  

    return result


# Creating a sample binary tree  
root = TreeNode(1)  
root.left = TreeNode(2)  
root.right = TreeNode(3)  
root.left.left = TreeNode(4)  
root.left.right = TreeNode(5)  

# Iterative Traversals  
print("Pre-order (Iterative):", pre_order_iterative(root))  
print("In-order (Iterative):", in_order_iterative(root))  
print("Post-order (Iterative):", post_order_iterative(root))

# Morris Traversals  
print("Morris In-order:", morris_in_order(root))  
print("Morris Pre-order:", morris_pre_order(root))