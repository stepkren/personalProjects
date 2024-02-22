#include <cassert>
#include <cstdarg>
#include <iomanip>
#include <cstdint>
#include <iostream>
#include <memory>
#include <limits>
#include <optional>
#include <array>
#include <random>
#include <type_traits>
#include <set>

template < typename T >
struct Ref {
  size_t size() const { return _data.size(); }
  const T* find(const T& value) const {
    auto it = _data.find(value);
    if (it == _data.end()) return nullptr;
    return &*it;
  }
  bool insert(const T& value) { return _data.insert(value).second; }
  bool erase(const T& value) { return _data.erase(value); }

  auto begin() const { return _data.begin(); }
  auto end() const { return _data.end(); }

  private:
  std::set<T> _data;
};


namespace config {
  inline constexpr bool CHECK_DEPTH = true;

  inline constexpr bool PARENT_POINTERS = true;
}

template < typename T >
struct Tree {

  struct Node{

    /**
     * Constructor
     * 
     * @param value
     * @param parent
    */
    Node ( const T& value, Node * parent )
    : m_height ( 1 ), m_value ( value ), m_left ( nullptr ), m_right ( nullptr ), m_parent ( parent )
    {}

    size_t m_height;

    T m_value;

    Node * m_left;
    Node * m_right;
    Node * m_parent;
  };

  /**
   * Recursive function to delete a node.
   * 
   * @param node A Node object to be deleted
  */
  void deleteNode ( Node * node ){
    if ( node != nullptr ){
      deleteNode ( node -> m_right );
      deleteNode ( node -> m_left );
      delete node;
    }
  }

  // Destructor
  ~Tree ( void ){
    deleteNode ( root );
  }

  /**
   * Return the size of the tree.
   * 
   * @return The size of the tree
  */
  size_t size() const { return m_size; }

  /**
   * Finds the element value in the tree.
   * 
   * @param value The value to be found in the tree
   * @return Pointer to the value
  */
  const T* find(const T& value) const{
    Node * curr = root;
    if ( curr == nullptr )
      return nullptr;

    while ( curr != nullptr ){
      if ( value == curr -> m_value ){
        return &curr -> m_value;
      }
      else if ( value < curr -> m_value )
        curr = curr -> m_left;
      else if ( value > curr -> m_value )
        curr = curr -> m_right;
    }
    return nullptr;
  }

  /**
   * Finds the node with the given value.
   * 
   * @param value The value of the node to be found
   * @return Node with the given value
  */
  std::pair<Node*, Node*> findNode ( const T& value ) const{
    Node * curr = root;
    Node * parent = nullptr;
    if ( curr == nullptr )
      return std::make_pair( curr, parent );

    while ( curr != nullptr ){
      if ( value == curr -> m_value ){
        return std::make_pair( curr, parent );
      }
      else if ( value < curr -> m_value ){
        parent = curr;
        curr = curr -> m_left;
      }
      else if ( value > curr -> m_value ){
        parent = curr;
        curr = curr -> m_right;
      }
    }

    return std::make_pair( nullptr, parent );
  }

  /**
   * Returns the height of a node.
   * 
   * @param node The node of which the height is to be returned
   * @return Height of the node
  */
  size_t getNodeHeight ( Node * node ){
    if ( node == nullptr )
      return 0;
    return node -> m_height;
  }

  /**
   * Return the balance on a specific node.
   * 
   * @param node The node whose balance we want to return
   * @return The balance on the given node
  */
  int getBalanceOnNode ( Node * node ){
    if ( node == nullptr )
      return 0;
    return ( getNodeHeight( node -> m_left ) - getNodeHeight( node -> m_right ) );
  }

  /**
   * Change the height of a node.
   * 
   * @param node The node whose height we want to change 
  */
  void changeHeight ( Node * node ){
    node -> m_height = std::max( getNodeHeight( node -> m_left ), getNodeHeight( node -> m_right ) ) + 1;
  }

  /**
   * Perform a left rotate on a specific node.
   * 
   * @param node The node on which we want to perform left rotate
   * @return The new node on the position of the node before the rotate
  */
  Node * leftRotate ( Node * node ){
    Node * rTmp = node -> m_right;
    Node * Sub = rTmp -> m_left;

    rTmp -> m_left = node;
    node -> m_right = Sub;

    rTmp -> m_parent = node -> m_parent;
    node -> m_parent = rTmp;
    if ( Sub != nullptr )
      Sub -> m_parent = node;
    if ( node -> m_parent -> m_parent != nullptr ){
      Node * parent = node -> m_parent -> m_parent;
      if ( parent -> m_value < node -> m_parent -> m_value ){
        parent -> m_right = node -> m_parent;
      }
      else if ( parent -> m_value > node -> m_parent -> m_value ){
        parent -> m_left = node -> m_parent;
      }
    }

    changeHeight ( node );
    changeHeight ( rTmp );

    return rTmp;
  }

  /**
   * Perform a right rotate on a specific node.
   * 
   * @param node The node on which we want to perform right rotate
   * @return The new node on the position of those node before the rotate
  */
  Node * rightRotate ( Node * node ){
    Node * lTmp = node -> m_left;
    Node * Sub = lTmp -> m_right;

    lTmp -> m_right = node;
    node -> m_left = Sub;

    lTmp -> m_parent = node -> m_parent;
    node -> m_parent = lTmp;
    if ( Sub != nullptr )
      Sub -> m_parent = node;

    if ( node -> m_parent -> m_parent != nullptr ){
      Node * parent = node -> m_parent -> m_parent;
      if ( parent -> m_value > node -> m_parent -> m_value ){
        parent -> m_left = node -> m_parent;
      }
      else if ( parent -> m_value < node -> m_parent -> m_value ){
        parent -> m_right = node -> m_parent;
      }
    }

    changeHeight ( node );
    changeHeight ( lTmp );

    return lTmp; 
  }

  /**
   * Balance a tree on a specific node.
   * 
   * @param node The node on which we want to balance the tree
  */
  void balanceTree ( Node * node ){
    Node * isRoot = nullptr;
    while ( node != nullptr ){
      changeHeight ( node );
      int balanceOnNode = getBalanceOnNode ( node );
      if ( balanceOnNode <= -2 ){
        if ( getBalanceOnNode ( node -> m_right ) > 0 ){
          isRoot = rightRotate ( node -> m_right );
        }
        isRoot = leftRotate ( node );
      }
      else if ( balanceOnNode >= 2 ){
        if ( getBalanceOnNode ( node -> m_left ) < 0 ){
          isRoot = leftRotate ( node -> m_left );
        }
        isRoot = rightRotate ( node );
      }
      node = node -> m_parent;      
    }
    if ( isRoot != nullptr && isRoot -> m_parent == nullptr )
      root = isRoot;    
  }

  /**
   * Insert a new node into the tree.
   * 
   * @param value The value of the new node
  */
  bool insert(T value){
    if ( root == nullptr ){
      root = new Node ( value, nullptr );
      m_size++;
      return true;
    }

    auto isFound = findNode ( value );
    Node * toBeBalancedFrom = nullptr;
    if ( isFound.first != nullptr )
      return false;

    if ( value < isFound.second -> m_value ){
      isFound.second -> m_left = new Node ( value, isFound.second );
      toBeBalancedFrom = isFound.second -> m_left;
    }

    else{
      isFound.second -> m_right = new Node ( value, isFound.second );
      toBeBalancedFrom = isFound.second -> m_right;      
    }

    m_size++;
    balanceTree ( toBeBalancedFrom );
    return true;
  }

  /**
   * Finds a successor of a given node.
   * 
   * @param node The node whose successor we want to find
   * @return The successor of the given nod
  */
  Node * findSuccessor ( Node * node ){
    return minInTree ( node -> m_right );
  }

  /**
   * Find the node with the minimum value in the tree.
   * 
   * @param node The root node of the tree in which we want to fund the minimum value
   * @return The node with the lowest value in the tree
  */
  Node * minInTree ( Node * node ){
    Node * curr = node;
    if ( curr -> m_left == nullptr )
      return curr;
    while ( curr -> m_left != nullptr ){
      curr = curr -> m_left;
    }

    return curr;
  }

  /**
   * Erase an element from the tree.
   * 
   * @param value The value that is to be erased from the tree
   * @return True if the element was successfully erased, False otherwise
  */
  bool erase(const T& value){
    auto isFound = findNode ( value );
    Node * toBeBalancedFrom = nullptr;
    // If node vith m_value == value isn't in tree then there isn't nothing to erase so return false
    if ( isFound.first == nullptr )
      return false;

    // No sons
    if ( isFound.first -> m_left == nullptr && isFound.first -> m_right == nullptr ){
      if ( isFound.first == root ){
        root = nullptr;
      }
      else if ( isFound.second -> m_value > value )
        isFound.second -> m_left = nullptr;
      else
        isFound.second -> m_right = nullptr;
      toBeBalancedFrom = isFound.first -> m_parent;        
    }
    // Only left son
    else if ( isFound.first -> m_left != nullptr && isFound.first -> m_right == nullptr ){
      if ( isFound.first == root ){
        root = isFound.first -> m_left;
      }
      else if ( isFound.second -> m_value > value )
        isFound.second -> m_left = isFound.first -> m_left;
      else
        isFound.second -> m_right = isFound.first -> m_left;
      isFound.first -> m_left -> m_parent = isFound.second;
      toBeBalancedFrom = isFound.first -> m_left;
    }
    // Only right son
    else if ( isFound.first -> m_left == nullptr && isFound.first -> m_right != nullptr ){
      if ( isFound.first == root ){
        root = isFound.first -> m_right;
      }
      else if ( isFound.second -> m_value > value )
        isFound.second -> m_left = isFound.first -> m_right;
      else
        isFound.second -> m_right = isFound.first -> m_right;
      isFound.first -> m_right -> m_parent = isFound.second;
      toBeBalancedFrom = isFound.first -> m_right;
    }
    // Both left and right son
    else if ( isFound.first -> m_left != nullptr && isFound.first -> m_right != nullptr ){
      Node * succ = findSuccessor ( isFound.first );
      T tmp = succ -> m_value;

      if ( succ -> m_right != nullptr ){
        succ -> m_right -> m_parent = succ -> m_parent;
        if ( succ != isFound.first -> m_right )
          succ -> m_parent -> m_left = succ -> m_right;
        else
          succ -> m_parent -> m_right = succ -> m_right;
      } 
      else{
        if ( succ != isFound.first -> m_right )
          succ -> m_parent -> m_left = succ -> m_right;
        else
          succ -> m_parent -> m_right = succ -> m_right;
      }
      isFound.first -> m_value = tmp;
      m_size--;
      Node * succParent = succ -> m_parent;
      delete succ;
      balanceTree ( succParent );     
      return true;
    }

    m_size--;
    delete isFound.first;
    balanceTree ( toBeBalancedFrom );
    return true;
  }

  // Needed to test the structure of the tree.
  // Replace Node with the real type of your nodes
  // and implementations with the ones matching
  // your attributes.
  struct TesterInterface {
    // using Node = ...
    static const Node *root(const Tree *t) { return t->root; }
    // Parent of root must be nullptr, ignore if config::PARENT_POINTERS == false
    static const Node *parent(const Node *n) { return n->m_parent; }
    static const Node *right(const Node *n) { return n->m_right; }
    static const Node *left(const Node *n) { return n->m_left; }
    static const T& value(const Node *n) { return n->m_value; }
  };

  size_t m_size = 0;
  Node * root = nullptr;
};



struct TestFailed : std::runtime_error {
  using std::runtime_error::runtime_error;
};

std::string fmt(const char *f, ...) {
  va_list args1;
  va_list args2;
  va_start(args1, f);
  va_copy(args2, args1);
  
  std::string buf(vsnprintf(nullptr, 0, f, args1), '\0');
  va_end(args1);
  
  vsnprintf(buf.data(), buf.size() + 1, f, args2);
  va_end(args2);

  return buf;
}

template < typename T >
struct Tester {
  Tester() = default;

  void size() const {
    size_t r = ref.size();
    size_t t = tested.size();
    if (r != t) throw TestFailed(fmt("Size: got %zu but expected %zu.", t, r));
  }

  void find(const T& x) const {
    auto r = ref.find(x);
    auto t = tested.find(x);
    bool found_r = r != nullptr;
    bool found_t = t != nullptr;

    if (found_r != found_t) _throw("Find mismatch", found_r);
    if (found_r && *t != x) throw TestFailed("Find: found different value");
  }

  void insert(const T& x, bool check_tree_ = false) {
    auto succ_r = ref.insert(x);
    auto succ_t = tested.insert(x);
    if (succ_r != succ_t) _throw("Insert mismatch", succ_r);
    size();
    if (check_tree_) check_tree();
  }

  void erase(const T& x, bool check_tree_ = false) {
    bool succ_r = ref.erase(x);
    auto succ_t = tested.erase(x);
    if (succ_r != succ_t) _throw("Erase mismatch", succ_r);
    size();
    if (check_tree_) check_tree();
  }

  struct NodeCheckResult {
    const T* min = nullptr;
    const T* max = nullptr;
    int depth = -1;
    size_t size = 0;
  };

  void check_tree() const {
    using TI = typename Tree<T>::TesterInterface;
    auto ref_it = ref.begin();
    bool check_value_failed = false;
    auto check_value = [&](const T& v) {
      if (check_value_failed) return;
      check_value_failed = (ref_it == ref.end() || *ref_it != v);
      if (!check_value_failed) ++ref_it;
    };

    auto r = check_node(TI::root(&tested), decltype(TI::root(&tested))(nullptr), check_value);
    size_t t_size = tested.size();

    if (t_size != r.size) throw TestFailed(
      fmt("Check tree: size() reports %zu but expected %zu.", t_size, r.size));

    if (check_value_failed) throw TestFailed(
      "Check tree: element mismatch");

    size();
  }

  template < typename Node, typename F >
  NodeCheckResult check_node(const Node* n, const Node* p, F& check_value) const {
    if (!n) return {};
    
    using TI = typename Tree<T>::TesterInterface;
    if constexpr(config::PARENT_POINTERS) {
      if (TI::parent(n) != p) throw TestFailed("Parent mismatch.");
    }

    auto l = check_node(TI::left(n), n, check_value);
    check_value(TI::value(n));
    auto r = check_node(TI::right(n), n, check_value);

    if (l.max && !(*l.max < TI::value(n)))
      throw TestFailed("Max of left subtree is too big.");
    if (r.min && !(TI::value(n) < *r.min))
      throw TestFailed("Min of right subtree is too small.");

    if (config::CHECK_DEPTH && abs(l.depth - r.depth) > 1) throw TestFailed(fmt(
      "Tree is not avl balanced: left depth %i and right depth %i.",
      l.depth, r.depth
    ));

    return {
      l.min ? l.min : &TI::value(n),
      r.max ? r.max : &TI::value(n),
      std::max(l.depth, r.depth) + 1, 1 + l.size + r.size
    };
  }

  static void _throw(const char *msg, bool s) {
    throw TestFailed(fmt("%s: ref %s.", msg, s ? "succeeded" : "failed"));
  }

  Tree<T> tested;
  Ref<T> ref;
};


void test_insert() {
  Tester<int> t;

  for (int i = 0; i < 10; i++) t.insert(i, true);
  for (int i = -10; i < 20; i++) t.find(i);

  for (int i = 0; i < 10; i++) t.insert((1 + i * 7) % 17, true);
  for (int i = -10; i < 20; i++) t.find(i);
}

void test_erase() {
  Tester<int> t;

  for (int i = 0; i < 10; i++) t.insert((1 + i * 7) % 17, true);
  for (int i = -10; i < 20; i++) t.find(i);

  for (int i = 3; i < 22; i += 2) t.erase(i, true);
  for (int i = -10; i < 20; i++) t.find(i);
  
  for (int i = 0; i < 10; i++) t.insert((1 + i * 13) % 17 - 8, true);
  for (int i = -10; i < 20; i++) t.find(i);
  
  for (int i = -4; i < 10; i++) t.erase(i, true);
  for (int i = -10; i < 20; i++) t.find(i);
}

enum RandomTestFlags : unsigned {
  SEQ = 1, NO_ERASE = 2, CHECK_TREE = 4
};

void test_random(size_t size, unsigned flags = 0) {
  Tester<size_t> t;
  std::mt19937 my_rand(24707 + size);

  bool seq = flags & SEQ;
  bool erase = !(flags & NO_ERASE);
  bool check_tree = flags & CHECK_TREE;

  for (size_t i = 0; i < size; i++)
    t.insert(seq ? 2*i : my_rand() % (3*size), check_tree);

  t.check_tree();

  for (size_t i = 0; i < 3*size + 1; i++) t.find(i);

  for (size_t i = 0; i < 30*size; i++) switch (my_rand() % 5) {
    case 1: t.insert(my_rand() % (3*size), check_tree);
      break;
    case 2: if (erase) t.erase(my_rand() % (3*size), check_tree);
      break;
    default:
      t.find(my_rand() % (3*size));
  }

  t.check_tree();
}

int main() {
  try {
    std::cout << "Insert test..." << std::endl;
    test_insert();

    std::cout << "Erase test..." << std::endl;
    test_erase();
    
    std::cout << "Tiny random test..." << std::endl;
    test_random(20, CHECK_TREE);
    
    std::cout << "Small random test..." << std::endl;
    test_random(200, CHECK_TREE);
    
    std::cout << "Big random test..." << std::endl;
    test_random(50'000);
    
    std::cout << "Big sequential test..." << std::endl;
    test_random(50'000, SEQ);

    std::cout << "All tests passed." << std::endl;
  } catch (const TestFailed& e) {
    std::cout << "Test failed: " << e.what() << std::endl;
  }
}



