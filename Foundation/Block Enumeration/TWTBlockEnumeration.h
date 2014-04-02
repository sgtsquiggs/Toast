//
//  TWTBlockEnumeration.h
//  Toast
//
//  Created by Prachi Gauriar on 1/21/2014.
//  Copyright (c) 2014 Two Toasters, LLC.
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to deal
//  in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in
//  all copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//  THE SOFTWARE.
//

#import <Foundation/Foundation.h>

#pragma mark Block Types

/*!
 @abstract Type for blocks that are given an object and return a object.
 @discussion This block type is used for collect operations.
 @param element The element being enumerated.
 @result An object.
 */
typedef id (^TWTBlockEnumerationCollectBlock)(id element);

/*!
 @abstract Type for blocks that when given an element return a BOOL.
 @discussion This block type is used for detect, select, and reject operations.
 @param element The element being enumerated.
 @result A boolean value.
 */
typedef BOOL (^TWTBlockEnumerationPredicateBlock)(id element);

/*!
 @abstract Type for blocks that, when given a total and an object, return an object with the element 
    (or some value derived from it).
 @discussion This block type is used for inject operations.
 @param memo Accumulator that is the result of the previous inject operation.
 @param element The element being enumerated.
 @result A new object representing the element's value injected into the total.
 */
typedef id (^TWTBlockEnumerationInjectBlock)(id memo, id element);

/*! 
 @abstract Protocol that exposes block enumeration methods.
 */
@protocol TWTBlockEnumeration <NSObject>

/*!
 @abstract Return a newly created collection that is the result of performing the given block on each
    element in the original collection.
 @discussion Given a collection of [1, 2, 3] and a block that returns the square of the element, this
    method will return [1, 4, 9]. If the result of the block is nil, that element in the resulting
    collection will be an instance of NSNull. If the original collection is a dictionary the key value
    is sent to the block not the value itself.
 @param block The block to invoke against each element of the collection.
 @result A new instance of the collection with the results of invoking the block on each element of
    the original collection.
 */
- (instancetype)twt_collectWithBlock:(TWTBlockEnumerationCollectBlock)block;

/*!
 @abstract Passes each entry in the collection to the block and returns the first item for which the 
    block returns YES.
 @discussion If the collection is a dictionary the key is passed to the predicate block.
 @param block Predicate block to apply to each item in the collection.
 @result Returns the first item for which the block returns YES. If no item returns YES, this will return nil.
 */
- (id)twt_detectWithBlock:(TWTBlockEnumerationPredicateBlock)block;

/*!
 @abstract Passes each item in the collection and a memo to the provided block starting with an initial
    object.
 @discussion Similar to a "reduce" operation. For each item in the collection, the memo value
    and the item is passed to the block. The return value from each iteration is the memo value for
    the next iteration. For the first iteration, the initial object is passed as the memo. For example, 
    given a collection of [1, 2, 3], a block that returns (memo + element), and an initial value of 0
    the returned value will be the result of (0 + 1) then (1 + 2) then (3 + 3) or 6. If the collection
    is a dictionary the value is the same, but the element is the key value.
 @param initialObject The initial object to pass as a memo to the first iteration of the collection.
 @param block An inject block that is performed on each element of the collection.
 @result The final returned value from the last iteration of the collection.
 */
- (id)twt_injectWithInitialObject:(id)initialObject block:(TWTBlockEnumerationInjectBlock)block;

/*!
 @abstract Passes each item in the collection to the block and returns a new collection with the items
    that returned YES from the block removed.
 @discussion If the collection is a dictionary the item pass to the block is the key value.
 @param block Predicate block to test items in the collection.
 @result A new instance of a collection with the items that were not rejected.
 */
- (instancetype)twt_rejectWithBlock:(TWTBlockEnumerationPredicateBlock)block;

/*!
 @abstract Passes each item in the collection to the block and returns a new collection with the items
    for which the block returned YES.
 @discussion If the collection is a dictionary the key value is passed to the block.
 @param block Predicate block to test items in the collection.
 @result A new array with the items that were selected.
 */
- (instancetype)twt_selectWithBlock:(TWTBlockEnumerationPredicateBlock)block;

@end

#pragma mark

@interface NSArray (TWTBlockEnumeration) <TWTBlockEnumeration>
@end

@interface NSDictionary (TWTBlockEnumeration) <TWTBlockEnumeration>
@end

@interface NSEnumerator (TWTBlockEnumeration) <TWTBlockEnumeration>
@end

@interface NSOrderedSet (TWTBlockEnumeration) <TWTBlockEnumeration>
@end

@interface NSSet (TWTBlockEnumeration) <TWTBlockEnumeration>
@end
