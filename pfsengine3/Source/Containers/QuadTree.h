#pragma once
#include "Container/Array.h"
#include "Math/Box.h"
// ----------------------------------------------------------------------------
template <typename T>
class PQuadTree
{
public:
	PQuadTree(const PBox& bounds = PBox(), unsigned int maxDepth = 20);
	PQuadTree(const PQuadTree& other) = delete;
	~PQuadTree();

	PQuadTree<T>& operator=(const PQuadTree& other) = delete;

	/**
	 * Add element into the tree.
	 */
	void Add(const T& data, const PBox& bounds);

	/**
	 * Finds all data intersecting position.
	 */
	PArray<T> FindData(const PVector2& position);

	/**
	 * Clear all data in tree.
	 */
	void Clear(const PBox& bounds);

private:
	struct PQuadTreeElement
	{
		T Data;
		PBox Bounds;
	};

	struct PQuadTreeNode
	{
		PBox Bounds;
		PArray<PQuadTreeElement> Elements;
		PQuadTreeNode* TopLeftChild = nullptr;
		PQuadTreeNode* TopRightChild = nullptr;
		PQuadTreeNode* BottomLeftChild = nullptr;
		PQuadTreeNode* BottomRightChild = nullptr;

	public:
		PQuadTreeNode(const PBox& bounds) :
			Bounds(bounds)
		{

		}
	};

private:
	PQuadTreeNode* _rootNode;
	PBox _bounds;
	unsigned int _maxDepth;

private:
	void Initialize(const PBox& bounds);

	static void SubdivideBounds(const PBox& bounds, PBox& OutTopLeft, PBox& OutTopRight, PBox& OutBottomLeft, PBox& OutBottomRight);

	/**
	 * Internal adding function. Start from node and recurse until placed. Return node where data is added.
	 */
	void* AddInternal(const T& data, const PBox& bounds, PQuadTreeNode* node, unsigned int depth = 0);

	/**
	 * 
	 */
	void FindDataInternal(const PVector2& position, PArray<T>& outData, PQuadTreeNode* node);

	/**
	 * Internal function for destroying the tree.
	 */
	void DestroyInternal(PQuadTreeNode* rootNode);

};
// ----------------------------------------------------------------------------
template <typename T>
PQuadTree<T>::PQuadTree(const PBox& bounds/* = PBox()*/, unsigned int maxDepth/* = 20*/):
	_maxDepth(maxDepth)
{
	Initialize(bounds);
}
// ----------------------------------------------------------------------------
template <typename T>
PQuadTree<T>::~PQuadTree()
{
	DestroyInternal(_rootNode);
}
// ----------------------------------------------------------------------------
template <typename T>
void PQuadTree<T>::Add(const T& data, const PBox& bounds)
{
	// The input bounds have to be completely contained to be added.
	if (!_bounds.DoesContain(bounds))
	{
		return;
	}

	AddInternal(data, bounds, _rootNode);
}
// ----------------------------------------------------------------------------
template <typename T>
PArray<T> PQuadTree<T>::FindData(const PVector2& position)
{
	static PArray<T> data;
	data.Clear(10);

	FindDataInternal(position, data, _rootNode);

	return data;
}
// ----------------------------------------------------------------------------
template <typename T>
void PQuadTree<T>::Clear(const PBox& bounds)
{
	DestroyInternal(_rootNode);
	Initialize(bounds);
}
// ----------------------------------------------------------------------------
template <typename T>
void PQuadTree<T>::Initialize(const PBox& bounds)
{
	_bounds = bounds;
	_rootNode = new PQuadTreeNode(bounds);
}
// ----------------------------------------------------------------------------
template <typename T>
void PQuadTree<T>::SubdivideBounds(const PBox& bounds, PBox& OutTopLeft, PBox& OutTopRight, PBox& OutBottomLeft, PBox& OutBottomRight)
{
	OutTopLeft		= PBox(PVector2(bounds.Min.X		, bounds.Min.Y)			, PVector2(bounds.Max.X / 2.f	, bounds.Max.Y / 2.f	));
	OutTopRight		= PBox(PVector2(bounds.Max.X / 2.f	, bounds.Min.Y)			, PVector2(bounds.Max.X			, bounds.Max.Y / 2.f	));
	OutBottomLeft	= PBox(PVector2(bounds.Min.X		, bounds.Max.Y / 2.f)	, PVector2(bounds.Max.X / 2.f	, bounds.Max.Y			));
	OutBottomRight  = PBox(PVector2(bounds.Max.X / 2.f	, bounds.Max.Y / 2.f)	, PVector2(bounds.Max.X			, bounds.Max.Y			));
}
// ----------------------------------------------------------------------------

template <typename T>
void* PQuadTree<T>::AddInternal(const T& data, const PBox& bounds, PQuadTreeNode* node, unsigned int depth/* = 0*/)
{
	if (depth >= _maxDepth)
	{
		node->Elements.Add(PQuadTreeElement{ data, bounds });
		return node;
	}

	// Check if any potential subnode contains data bounds
	PBox subdivisionBoxes[4];
	enum ESubdivisionBox : int
	{
		TLBounds = 0,
		TRBounds = 1,
		BLBounds = 2,
		BRBounds = 3
	};

	SubdivideBounds(node->Bounds, subdivisionBoxes[TLBounds], subdivisionBoxes[TRBounds], subdivisionBoxes[BLBounds], subdivisionBoxes[BRBounds]);

	int boxIndex = -1;
	for (int i = 0; i < 4; ++i)
	{
		if (subdivisionBoxes[i].DoesContain(bounds))
		{
			if (boxIndex == -1)
			{
				boxIndex = i;
				break;
			}
		}
	}

	if (boxIndex == -1)
	{
		// Not contained by any subdivisions. Add to current node.
		node->Elements.Add(PQuadTreeElement{ data, bounds });
		return node;
	}

	// Subdivide given node
	node->TopLeftChild		= new PQuadTreeNode(subdivisionBoxes[TLBounds]);
	node->TopRightChild		= new PQuadTreeNode(subdivisionBoxes[TRBounds]);
	node->BottomLeftChild	= new PQuadTreeNode(subdivisionBoxes[BLBounds]);
	node->BottomRightChild	= new PQuadTreeNode(subdivisionBoxes[BRBounds]);

	// Move to next level
	switch (boxIndex)
	{
		case TLBounds:
		{
			return AddInternal(data, bounds, node->TopLeftChild, depth + 1);
			break;
		}
		case TRBounds:
		{
			return AddInternal(data, bounds, node->TopRightChild, depth + 1);
			break;
		}
		case BLBounds:
		{
			return AddInternal(data, bounds, node->BottomLeftChild, depth + 1);
			break;
		}
		case BRBounds:
		{
			return AddInternal(data, bounds, node->BottomRightChild, depth + 1);
			break;
		}
	}

	return nullptr;
}
// ----------------------------------------------------------------------------
template <typename T>
void PQuadTree<T>::FindDataInternal(const PVector2& position, PArray<T>& outData, PQuadTreeNode* node)
{
	if (node == nullptr)
	{
		return;
	}

	// Add current elements to list
	for (const PQuadTreeElement& element : node->Elements)
	{
		if (element.Bounds.DoesContain(position))
		{
			outData.Add(element.Data);
		}
	}

	const PVector2 nodeBoundsCenter = node->Bounds.GetCenter();
	PQuadTreeNode* nextNode = nullptr;
	if (position.X < nodeBoundsCenter.X)
	{
		nextNode = position.Y < nodeBoundsCenter.Y ? node->TopLeftChild : node->BottomLeftChild;
	}
	else
	{
		nextNode = position.Y < nodeBoundsCenter.Y ? node->TopRightChild : node->BottomRightChild;
	}

	if (nextNode != nullptr)
	{
		FindDataInternal(position, outData, nextNode);
	}
}
// ----------------------------------------------------------------------------
template <typename T>
void PQuadTree<T>::DestroyInternal(PQuadTreeNode* rootNode)
{
	if (rootNode->TopLeftChild != nullptr)
	{
		DestroyInternal(rootNode->TopLeftChild);
	}
	if (rootNode->TopRightChild != nullptr)
	{
		DestroyInternal(rootNode->TopRightChild);
	}
	if (rootNode->BottomLeftChild != nullptr)
	{
		DestroyInternal(rootNode->BottomLeftChild);
	}
	if (rootNode->BottomRightChild != nullptr)
	{
		DestroyInternal(rootNode->BottomRightChild);
	}

	delete rootNode;
}
// ----------------------------------------------------------------------------