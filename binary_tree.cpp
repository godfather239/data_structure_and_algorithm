// main.cpp
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string>
#include <deque>
using namespace std;

struct TreeNode
{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(NULL), right(NULL) {}
};

TreeNode* create_binsearch_tree(int* vals, int cnt);
TreeNode* find_insert_pos(TreeNode* head, TreeNode* node);
TreeNode* tree_to_linklist(TreeNode* root);
void helper(TreeNode* root, TreeNode*& head, TreeNode*& tail);
void preorder_traverse(TreeNode* root);
void level_traverse(TreeNode* root);
void print_linklist(TreeNode* head);
// Check if tree c is the sub tree of tree p.
bool is_sub_tree(TreeNode* p, TreeNode* c);
bool has_equal_tree(TreeNode* a, TreeNode* b);

TreeNode* create_binsearch_tree(int* vals, int cnt)
{
    TreeNode* head = new TreeNode;
    head->val = vals[0];
    for (int i = 1; i < cnt; ++i) {
        TreeNode* node = new TreeNode;
        node->val = vals[i];
        // Find the insert position
        TreeNode* pos = find_insert_pos(head, node);
        assert(pos != NULL);
        if (pos->val < node->val) {
            pos->right = node;
        } else {
            pos->left = node;
        }
    }
    return head;
}

TreeNode* find_insert_pos(TreeNode* head, TreeNode* node)
{
    TreeNode* prev = NULL;
    while (head) {
        prev = head;
        if (head->val < node->val) {
            head = head->right;
        } else {
            head = head->left;
        }
    }
    return prev;
}

void preorder_traverse(TreeNode* root)
{
    if (!root)
        return;
    printf("%d ", root->val);
    preorder_traverse(root->left);
    preorder_traverse(root->right);
}

void level_traverse(TreeNode* root)
{
    if (!root)
        return;
    struct Item {
        int level;
        TreeNode* node;
        Item(int l, TreeNode* n) : level(l), node(n) {}
    };
    deque<Item> queue;
    int level = 0;
    queue.push_back(Item(level, root));
    while (!queue.empty()) {
        const Item& it = queue.front();
        queue.pop_front();
        printf("level:%d,val:%d; ", it.level, it.node->val);
        if (it.node->left)
            queue.push_back(Item(it.level+1, it.node->left));
        if (it.node->right)
            queue.push_back(Item(it.level+1, it.node->right));
    }
}

void print_linklist(TreeNode* head)
{
    while (head) {
        printf("%d ", head->val);
        head = head->right;
    }
}

TreeNode* tree_to_linklist(TreeNode* root)
{
    if (!root)
        return NULL;
    TreeNode* head = NULL;
    TreeNode* tail = NULL;
    helper(root, head, tail);
    return head;
}

void helper(TreeNode* root, TreeNode*& head, TreeNode*& tail)
{
    if (!root) {
        head = NULL;
        tail = NULL;
        return;
    }
    TreeNode* llink_head = NULL;
    TreeNode* llink_tail = NULL;
    helper(root->left, llink_head, llink_tail);
    TreeNode* rlink_head = NULL;
    TreeNode* rlink_tail = NULL;
    helper(root->right, rlink_head, rlink_tail);
    if (llink_tail) {
        llink_tail->right = root;
        root->left = llink_tail;
        head = llink_head;
    } else {
        head = root;
    }
    root->right = rlink_head;
    if (rlink_head) {
        rlink_head->left = root;
        tail = rlink_tail;
    } else {
        tail = root;
    }
}

bool is_sub_tree(TreeNode* p, TreeNode* c)
{
    if (p && !c) {
        return true;
    } else if (!p && c) {
        return false;
    } else if (!p && !c) {
        return true;
    } else {
        if (has_equal_tree(p, c)) {
            return true;
        } else {
            return is_sub_tree(p->left, c) || is_sub_tree(p->right, c);
        }
    }
}

bool has_equal_tree(TreeNode* a, TreeNode* b)
{
    if (!b) {
        return true;
    } else {
        if (a) {
            return (a->val == b->val) && has_equal_tree(a->left, b->left) && 
                has_equal_tree(a->right, b->right);
        } else {
            return false;
        }
    }
}

int main(int argc, char* argv[])
{
    int arr[10] = {8, 3, 4, 7, 6, 1, 9, 10, 2, 20};
    TreeNode* p = create_binsearch_tree(arr, 10);
    TreeNode* c = create_binsearch_tree(arr+1, 2);
    printf("level traverse: ");
    level_traverse(c);
    printf("\n");
    printf("is sub tree: %d\n", is_sub_tree(p, c));
    c = create_binsearch_tree(arr+2, 2);
    printf("is sub tree: %d\n", is_sub_tree(p, c));
    c = create_binsearch_tree(arr+2, 3);
    printf("is sub tree: %d\n", is_sub_tree(p, c));
    c = create_binsearch_tree(arr+2, 4);
    printf("is sub tree: %d\n", is_sub_tree(p, c));

//    printf("After creation, the tree in preorder is: ");
//    preorder_traverse(root);
//    printf("\nlevel traverse: ");
//    level_traverse(root);
//    TreeNode* head = tree_to_linklist(root);
//    printf("\nAfter transform to linklist,:");
//    print_linklist(head);
//    printf("\n");
    return 0;
}
