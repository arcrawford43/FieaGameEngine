#pragma once
#include <glm/glm.hpp>
#include <string>
#include <cstddef>
#include "RTTI.h"

namespace FieaGameEngine
{
	class Scope;
	class Attributed;
	enum class DatumTypes
	{
		Unknown,
		Integer,
		Float,
		Vector,
		Matrix,
		String,
		Table,
		Pointer
	};

	class Datum final
	{
	public:
		friend Attributed;
		friend Scope;
		/// <summary>
		/// Default 
		/// </summary>
		Datum() = default;

		/// <summary>
		/// Destructor that frees all memory if internal storage
		/// </summary>
		~Datum();

		/// <summary>
		/// Copy Constructor
		/// </summary>
		/// <param name="other">
		/// Datum being copied
		/// </param>
		Datum(const Datum& other);

		/// <summary>
		/// Copy Assignment Operator
		/// </summary>
		/// <param name="other">Datum being copied</param>
		/// <returns>Datum being copied to</returns>
		Datum& operator=(const Datum& other);

		/// <summary>
		/// Move Constructor
		/// </summary>
		/// <param name="rhs">Datum being moved</param>
		Datum(Datum&& rhs) noexcept;

		/// <summary>
		/// Move Assignmenmt Operator
		/// </summary>
		/// <param name="rhs">Datum being moved</param>
		/// <returns>Datum being moved to</returns>
		Datum& operator=(Datum&& rhs) noexcept;

		/// <summary>
		/// Integer Typecast constructor
		/// </summary>
		/// <param name="other">Value being assigned</param>
		Datum(std::int32_t value);

		/// <summary>
		/// Float Typecast constructor
		/// </summary>
		/// <param name="other">Value being assigned</param>
		Datum(float value);

		/// <summary>
		/// Vector Typecast constructor
		/// </summary>
		/// <param name="other">Value being assigned</param>
		Datum(const glm::vec4& value);

		/// <summary>
		/// Matrix Typecast constructor
		/// </summary>
		/// <param name="other">Value being assigned</param>
		Datum(const glm::mat4& value);
		
		/// /// <summary>
		/// String Typecast constructor
		/// </summary>
		/// <param name="other">Value being assigned</param>
		Datum(const std::string& value);

		/// /// <summary>
		/// String Typecast constructor
		/// </summary>
		/// <param name="other">Value being assigned</param>
		Datum(std::string&& value);
		
		/// <summary>
		/// RTTI Pointer Typecast constructor
		/// </summary>
		/// <param name="other">Value being assigned</param>
		Datum(RTTI& value);

		/// <summary>
		/// RTTI Pointer Typecast constructor
		/// </summary>
		/// <param name="other">Value being assigned</param>
		Datum(RTTI* value);

		/// <summary>
		/// Integer Assignment Operator
		/// </summary>
		/// <exception cref="runtime_error">Cannot use assignment operator on Datum that has a known type</exception>
		/// <param name="other">Value being assigned</param>
		/// <returns>Datum being copied to</returns>
		Datum& operator=(std::int32_t value);

		/// <summary>
		/// Float Assignment Operator
		/// </summary>
		/// <exception cref="runtime_error">Cannot use assignment operator on Datum that has a known type</exception>
		/// <param name="other">Value being assigned</param>
		/// <returns>Datum being copied to</returns>
		Datum& operator=(float value);

		/// <summary>
		/// Vector Assignment Operator
		/// </summary>
		/// <exception cref="runtime_error">Cannot use assignment operator on Datum that has a known type</exception>
		/// <param name="other">Value being assigned</param>
		/// <returns>Datum being copied to</returns>
		Datum& operator=(const glm::vec4& value);

		/// <summary>
		/// Matrix Assignment Operator
		/// </summary>
		/// <exception cref="runtime_error">Cannot use assignment operator on Datum that has a known type</exception>
		/// <param name="other">Value being assigned</param>
		/// <returns>Datum being copied to</returns>
		Datum& operator=(const glm::mat4& value);

		/// <summary>
		/// String Assignment Operator
		/// </summary>
		/// <exception cref="runtime_error">Cannot use assignment operator on Datum that has a known type</exception>
		/// <param name="other">Value being assigned</param>
		/// <returns>Datum being copied to</returns>
		Datum& operator=(const std::string& value);

		/// <summary>
		/// String Assignment Operator
		/// </summary>
		/// <exception cref="runtime_error">Cannot use assignment operator on Datum that has a known type</exception>
		/// <param name="other">Value being assigned</param>
		/// <returns>Datum being copied to</returns>
		Datum& operator=(std::string&& value);

		/// <summary>
		/// RTTI Pointer Assignment Operator
		/// </summary>
		/// <exception cref="runtime_error">Cannot use assignment operator on Datum that has a known type</exception>
		/// <param name="other">Value being assigned</param>
		/// <returns>Datum being copied to</returns>
		Datum& operator=(RTTI& value);

		/// <summary>
		/// RTTI Pointer Assignment Operator
		/// </summary>
		/// <exception cref="runtime_error">Cannot use assignment operator on Datum that has a known type</exception>
		/// <param name="other">Value being assigned</param>
		/// <returns>Datum being copied to</returns>
		Datum& operator=(RTTI* value);

		/// <summary>
		/// Compares if two Datums are equivalent
		/// </summary>
		/// <param name="other">Datum being compared to</param>
		/// <returns>true if equivalent and false if not</returns>
		bool operator==(const Datum& other) const;

		/// <summary>
		/// Compares if two Datums are not equivalent
		/// </summary>
		/// <param name="other">Datum being compared to</param>
		/// <returns>true if not equivalent and false if equivalent/returns>
		bool operator!=(const Datum& other) const;

		/// <summary>
		/// Compares if first element in Datum is equivalent to an integer
		/// </summary>
		/// <exception cref="runtime_error">Datum is incorrect type for this comparison</exception>
		/// <exception cref="runtime_error">Cannot compare empty Datum</exception>
		/// <param name="other">integer being compared to</param>
		/// <returns>true if equivalent and false if not</returns>
		bool operator==(std::int32_t other) const;

		/// <summary>
		/// Compares if first element in Datum is not equivalent to an integer
		/// </summary>
		/// <exception cref="runtime_error">Datum is incorrect type for this comparison</exception>
		/// <exception cref="runtime_error">Cannot compare empty Datum</exception>
		/// <param name="other">integer being compared to</param>
		/// <returns>true if not equivalent and false if equivalent/returns>
		bool operator!=(std::int32_t other) const;

		/// <summary>
		/// Compares if first element in Datum is equivalent to a float
		/// </summary>
		/// <exception cref="runtime_error">Datum is incorrect type for this comparison</exception>
		/// <exception cref="runtime_error">Cannot compare empty Datum</exception>
		/// <param name="other">integer being compared to</param>
		/// <returns>true if equivalent and false if not</returns>
		bool operator==(float other) const;

		/// <summary>
		/// Compares if first element in Datum is not equivalent to a float
		/// </summary>
		/// <exception cref="runtime_error">Datum is incorrect type for this comparison</exception>
		/// <exception cref="runtime_error">Cannot compare empty Datum</exception>
		/// <param name="other">integer being compared to</param>
		/// <returns>true if not equivalent and false if equivalent/returns>
		bool operator!=(float other) const;

		/// <summary>
		/// Compares if first element in Datum is equivalent to a vec4
		/// </summary>
		/// <exception cref="runtime_error">Datum is incorrect type for this comparison</exception>
		/// <exception cref="runtime_error">Cannot compare empty Datum</exception>
		/// <param name="other">integer being compared to</param>
		/// <returns>true if equivalent and false if not</returns>
		bool operator==(const glm::vec4& other) const;

		/// <summary>
		/// Compares if first element in Datum is not equivalent to a vec4
		/// </summary>
		/// <exception cref="runtime_error">Datum is incorrect type for this comparison</exception>
		/// <exception cref="runtime_error">Cannot compare empty Datum</exception>
		/// <param name="other">integer being compared to</param>
		/// <returns>true if not equivalent and false if equivalent/returns>
		bool operator!=(const glm::vec4& other) const;

		/// <summary>
		/// Compares if first element in Datum is equivalent to a mat4
		/// </summary>
		/// <exception cref="runtime_error">Datum is incorrect type for this comparison</exception>
		/// <exception cref="runtime_error">Cannot compare empty Datum</exception>
		/// <param name="other">integer being compared to</param>
		/// <returns>true if equivalent and false if not</returns>
		bool operator==(const glm::mat4& other) const;

		/// <summary>
		/// Compares if first element in Datum is not equivalent to a mat4
		/// </summary>
		/// <exception cref="runtime_error">Datum is incorrect type for this comparison</exception>
		/// <exception cref="runtime_error">Cannot compare empty Datum</exception>
		/// <param name="other">integer being compared to</param>
		/// <returns>true if not equivalent and false if equivalent/returns>
		bool operator!=(const glm::mat4& other) const;

		/// <summary>
		/// Compares if first element in Datum is equivalent to a string
		/// </summary>
		/// <exception cref="runtime_error">Datum is incorrect type for this comparison</exception>
		/// <exception cref="runtime_error">Cannot compare empty Datum</exception>
		/// <param name="other">integer being compared to</param>
		/// <returns>true if equivalent and false if not</returns>
		bool operator==(const std::string& other) const;

		/// <summary>
		/// Compares if first element in Datum is not equivalent to a string
		/// </summary>
		/// <exception cref="runtime_error">Datum is incorrect type for this comparison</exception>
		/// <exception cref="runtime_error">Cannot compare empty Datum</exception>
		/// <param name="other">integer being compared to</param>
		/// <returns>true if not equivalent and false if equivalent/returns>
		bool operator!=(const std::string& other) const;

		/// <summary>
		/// Compares if first element in Datum is equivalent to a RTTI pointer
		/// </summary>
		/// <exception cref="runtime_error">Datum is incorrect type for this comparison</exception>
		/// <exception cref="runtime_error">Cannot compare empty Datum</exception>
		/// <param name="other">integer being compared to</param>
		/// <returns>true if equivalent and false if not</returns>
		bool operator==(RTTI* other) const;

		/// <summary>
		/// Compares if first element in Datum is not equivalent to a RTTI pointer
		/// </summary>
		/// <exception cref="runtime_error">Datum is incorrect type for this comparison</exception>
		/// <exception cref="runtime_error">Cannot compare empty Datum</exception>
		/// <param name="other">integer being compared to</param>
		/// <returns>true if not equivalent and false if equivalent/returns>
		bool operator!=(RTTI* other) const;

		/// <summary>
		/// Increases capacity of Datum 
		/// </summary>
		/// <exception cref="runtime_error">Cannot reserve size for an Unknown type</exception>
		/// <param name="capacity">Value to increase capacity to</param>
		void Reserve(std::size_t capacity);

		/// <summary>
		/// Sets the type of an Unknown Datum
		/// </summary>
		/// <exception cref="runtime_error">Cannot change type of datum that is not Unknown</exception>
		/// <exception cref="runtime_error">Cannot set type to be Unknown</exception>
		/// <param name="type">The type that the Datum is being set to</param>
		void SetType(DatumTypes type);

		/// <summary>
		/// Returns type of Datum
		/// </summary>
		/// <returns>DatumTypes that is the type of the Datum</returns>
		DatumTypes Type() const;

		/// <summary>
		/// Resizes the Datum and makes the capacity the same as the size
		/// </summary>
		/// <exception cref="runtime_error">Cannot Resize Datum with Unknown type</exception>
		/// <param name="size">Size for Datum to be set to</param>
		void Resize(std::size_t size);

		/// <summary>
		/// Returns size of Datum
		/// </summary>
		/// <returns>The size of Datum</returns>
		std::size_t Size() const;
		
		/// <summary>
		/// Returns capacity of Datum
		/// </summary>
		/// <returns>The size of Datum</returns>
		std::size_t Capacity() const;

		/// <summary>
		/// Sets a value in Datum
		/// </summary>
		/// <exception cref="runtime_error">Datum type is not Integer</exception>
		/// <exception cref="out_of_range">Index is not a valid index in Datum</exception>
		/// <param name="value">Value to set index to</param>
		/// <param name="index">index to be set</param>
		void Set(std::int32_t value, std::size_t index = 0);

		/// <summary>
		/// Sets a value in Datum
		/// </summary>
		/// <exception cref="runtime_error">Datum type is not Float</exception>
		/// <exception cref="out_of_range">Index is not a valid index in Datum</exception>
		/// <param name="value">Value to set index to</param>
		/// <param name="index">index to be set</param>
		void Set(float value, std::size_t index = 0);

		/// <summary>
		/// Sets a value in Datum
		/// </summary>
		/// <exception cref="runtime_error">Datum type is not Vector</exception>
		/// <exception cref="out_of_range">Index is not a valid index in Datum</exception>
		/// <param name="value">Value to set index to</param>
		/// <param name="index">index to be set</param>
		void Set(const glm::vec4& value, std::size_t index = 0);

		/// <summary>
		/// Sets a value in Datum
		/// </summary>
		/// <exception cref="runtime_error">Datum type is not Matrix</exception>
		/// <exception cref="out_of_range">Index is not a valid index in Datum</exception>
		/// <param name="value">Value to set index to</param>
		/// <param name="index">index to be set</param>
		void Set(const glm::mat4& value, std::size_t index = 0);

		/// <summary>
		/// Sets a value in Datum
		/// </summary>
		/// <exception cref="runtime_error">Datum type is not String</exception>
		/// <exception cref="out_of_range">Index is not a valid index in Datum</exception>
		/// <param name="value">Value to set index to</param>
		/// <param name="index">index to be set</param>
		void Set(const std::string& value, std::size_t index = 0);

		/// <summary>
		/// Sets a value in Datum
		/// </summary>
		/// <exception cref="runtime_error">Datum type is not String</exception>
		/// <exception cref="out_of_range">Index is not a valid index in Datum</exception>
		/// <param name="value">Value to set index to</param>
		/// <param name="index">index to be set</param>
		void Set(std::string&& value, std::size_t index = 0);

		/// <summary>
		/// Sets a value in Datum
		/// </summary>
		/// <exception cref="runtime_error">Datum type is not Pointer</exception>
		/// <exception cref="out_of_range">Index is not a valid index in Datum</exception>
		/// <param name="value">Value to set index to</param>
		/// <param name="index">index to be set</param>
		void Set(RTTI& value, std::size_t index = 0);

		/// <summary>
		/// Gets a value in Datum
		/// </summary>
		/// <exception cref="runtime_error">Datum type is not Integer</exception>
		/// <exception cref="out_of_range">Index is not a valid index in Datum</exception>
		/// <param name="index">index to get</param>
		/// <returns>A reference to the integer</returns>
		std::int32_t& GetInteger(std::size_t index = 0);

		/// <summary>
		/// Gets a const value in Datum
		/// </summary>
		/// <exception cref="runtime_error">Datum type is not Integer</exception>
		/// <exception cref="out_of_range">Index is not a valid index in Datum</exception>
		/// <param name="index">index to get</param>
		/// <returns>A const reference to the integer</returns>
		std::int32_t GetInteger(std::size_t index = 0) const;

		/// <summary>
		/// Gets a value in Datum
		/// </summary>
		/// <exception cref="runtime_error">Datum type is not Float</exception>
		/// <exception cref="out_of_range">Index is not a valid index in Datum</exception>
		/// <param name="index">index to get</param>
		/// <returns>A reference to the float</returns>
		float& GetFloat(std::size_t index = 0);

		/// <summary>
		/// Gets a const value in Datum
		/// </summary>
		/// <exception cref="runtime_error">Datum type is not Float</exception>
		/// <exception cref="out_of_range">Index is not a valid index in Datum</exception>
		/// <param name="index">index to get</param>
		/// <returns>A const reference to the float</returns>
		float GetFloat(std::size_t index = 0) const;

		/// <summary>
		/// Gets a value in Datum
		/// </summary>
		/// <exception cref="runtime_error">Datum type is not Vector</exception>
		/// <exception cref="out_of_range">Index is not a valid index in Datum</exception>
		/// <param name="index">index to get</param>
		/// <returns>A reference to the vec4</returns>
		glm::vec4& GetVector(std::size_t index = 0);

		/// <summary>
		/// Gets a const value in Datum
		/// </summary>
		/// <exception cref="runtime_error">Datum type is not Vector</exception>
		/// <exception cref="out_of_range">Index is not a valid index in Datum</exception>
		/// <param name="index">index to get</param>
		/// <returns>A const reference to the vec4</returns>
		const glm::vec4& GetVector(std::size_t index = 0) const;

		/// <summary>
		/// Gets a value in Datum
		/// </summary>
		/// <exception cref="runtime_error">Datum type is not Matrix</exception>
		/// <exception cref="out_of_range">Index is not a valid index in Datum</exception>
		/// <param name="index">index to get</param>
		/// <returns>A reference to the mat4</returns>
		glm::mat4& GetMatrix(std::size_t index = 0);

		/// <summary>
		/// Gets a const value in Datum
		/// </summary>
		/// <exception cref="runtime_error">Datum type is not Matrix</exception>
		/// <exception cref="out_of_range">Index is not a valid index in Datum</exception>
		/// <param name="index">index to get</param>
		/// <returns>A const reference to the mat4</returns>
		const glm::mat4& GetMatrix(std::size_t index = 0) const;

		/// <summary>
		/// Gets a value in Datum
		/// </summary>
		/// <exception cref="runtime_error">Datum type is not String</exception>
		/// <exception cref="out_of_range">Index is not a valid index in Datum</exception>
		/// <param name="index">index to get</param>
		/// <returns>A reference to the string</returns>
		std::string& GetString(std::size_t index = 0);

		/// <summary>
		/// Gets a const value in Datum
		/// </summary>
		/// <exception cref="runtime_error">Datum type is not String</exception>
		/// <exception cref="out_of_range">Index is not a valid index in Datum</exception>
		/// <param name="index">index to get</param>
		/// <returns>A const reference to the string</returns>
		const std::string& GetString(std::size_t index = 0) const;

		/// <summary>
		/// Gets a value in Datum
		/// </summary>
		/// <exception cref="runtime_error">Datum type is not Pointer</exception>
		/// <exception cref="out_of_range">Index is not a valid index in Datum</exception>
		/// <param name="index">index to get</param>
		/// <returns>A pointer to the RTTI</returns>
		RTTI*& GetPointer(std::size_t index = 0);

		/// <summary>
		/// Gets a const value in Datum
		/// </summary>
		/// <exception cref="runtime_error">Datum type is not Pointer</exception>
		/// <exception cref="out_of_range">Index is not a valid index in Datum</exception>
		/// <param name="index">index to get</param>
		/// <returns>A const pointer to the RTTI</returns>
		const RTTI* GetPointer(std::size_t index = 0) const;

		/// <summary>
		/// Gets a value in Datum
		/// </summary>
		/// <exception cref="runtime_error">Datum type is not Pointer</exception>
		/// <exception cref="out_of_range">Index is not a valid index in Datum</exception>
		/// <param name="index">index to get</param>
		/// <returns>A pointer to the RTTI</returns>
		Scope*& GetTable(std::size_t index = 0);

		/// <summary>
		/// Gets a const value in Datum
		/// </summary>
		/// <exception cref="runtime_error">Datum type is not Pointer</exception>
		/// <exception cref="out_of_range">Index is not a valid index in Datum</exception>
		/// <param name="index">index to get</param>
		/// <returns>A const pointer to the RTTI</returns>
		const Scope* GetTable(std::size_t index = 0) const;

		/// <summary>
		/// Adds an integer value to the back of the Datum
		/// </summary>
		/// <exception cref="runtime_error">Must be type Integer to insert an integer</exception>
		/// <param name="value">Interger being added</param>
		void PushBack(std::int32_t value);

		/// <summary>
		/// Adds a float value to the back of the Datum
		/// </summary>
		/// <exception cref="runtime_error">Must be type Float to insert a float</exception>
		/// <param name="value">Float being added</param>
		void PushBack(float value);

		/// <summary>
		/// Adds a vec4 value to the back of the Datum
		/// </summary>
		/// <exception cref="runtime_error">Must be type Vector to insert a vec4</exception>
		/// <param name="value">Vec4 being added</param>
		void PushBack(const glm::vec4& value);

		/// <summary>
		/// Adds a mat4 value to the back of the Datum
		/// </summary>
		/// <exception cref="runtime_error">Must be type Matrix to insert a mat4</exception>
		/// <param name="value">Mat4 being added</param>
		void PushBack(const glm::mat4& value);

		/// <summary>
		/// Adds a string value to the back of the Datum
		/// </summary>
		/// <exception cref="runtime_error">Must be type String to insert a string</exception>
		/// <param name="value">String being added</param>
		void PushBack(const std::string& value);

		/// <summary>
		/// Adds a string value to the back of the Datum
		/// </summary>
		/// <exception cref="runtime_error">Must be type String to insert a string</exception>
		/// <param name="value">String being added</param>
		void PushBack(std::string&& value);

		/// <summary>
		/// Adds a RTTI pointer to the back of the Datum
		/// </summary>
		/// <exception cref="runtime_error">Must be type Pointer to insert a RTTI pointer</exception>
		/// <param name="value">RTTI pointer being added</param>
		void PushBack(RTTI& value);

		/// <summary>
		/// Removes the last element from a Datum
		/// </summary>
		/// <exception cref="runtime_error">Cannot PopBack on Unknown Type</exception>
		void PopBack();

		/// <summary>
		/// Gets the front value in Datum
		/// </summary>
		/// <exception cref="runtime_error">Datum type is not Integer</exception>
		/// <returns>A reference to the integer</returns>
		std::int32_t& FrontInteger();

		/// <summary>
		/// Gets the front const value in Datum
		/// </summary>
		/// <exception cref="runtime_error">Datum type is not Integer</exception>
		/// <returns>A const reference to the integer</returns>
		std::int32_t FrontInteger() const;

		/// <summary>
		/// Gets the front value in Datum
		/// </summary>
		/// <exception cref="runtime_error">Datum type is not Float</exception>
		/// <returns>A reference to the float</returns>
		float& FrontFloat();

		/// <summary>
		/// Gets the front value in Datum
		/// </summary>
		/// <exception cref="runtime_error">Datum type is not Float</exception>
		/// <returns>A const reference to the float</returns>
		float FrontFloat() const;

		/// <summary>
		/// Gets the front value in Datum
		/// </summary>
		/// <exception cref="runtime_error">Datum type is not Vector</exception>
		/// <returns>A reference to the vec4</returns>
		glm::vec4& FrontVector();

		/// <summary>
		/// Gets the front const value in Datum
		/// </summary>
		/// <exception cref="runtime_error">Datum type is not Vector</exception>
		/// <returns>A const reference to the vec4</returns>
		const glm::vec4& FrontVector() const;

		/// <summary>
		/// Gets the front value in Datum
		/// </summary>
		/// <exception cref="runtime_error">Datum type is not Matrix</exception>
		/// <returns>A reference to the mat4</returns>
		glm::mat4& FrontMatrix();

		/// <summary>
		/// Gets the front const value in Datum
		/// </summary>
		/// <exception cref="runtime_error">Datum type is not Matrix</exception>
		/// <returns>A const reference to the mat4</returns>
		const glm::mat4& FrontMatrix() const;

		/// <summary>
		/// Gets the front value in Datum
		/// </summary>
		/// <exception cref="runtime_error">Datum type is not String</exception>
		/// <returns>A reference to the string</returns>
		std::string& FrontString();

		/// <summary>
		/// Gets the front const value in Datum
		/// </summary>
		/// <exception cref="runtime_error">Datum type is not String</exception>
		/// <returns>A const reference to the string</returns>
		const std::string& FrontString() const;

		/// <summary>
		/// Gets the front value in Datum
		/// </summary>
		/// <exception cref="runtime_error">Datum type is not Pointer</exception>
		/// <returns>A pointer to the RTTI</returns>
		RTTI*& FrontPointer();

		/// <summary>
		/// Gets the front const value in Datum
		/// </summary>
		/// <exception cref="runtime_error">Datum type is not Pointer</exception>
		/// <returns>A const pointer to the RTTI</returns>
		const RTTI* FrontPointer() const;

		/// <summary>
		/// Gets the Back value in Datum
		/// </summary>
		/// <exception cref="runtime_error">Datum type is not Integer</exception>
		/// <returns>A reference to the integer</returns>
		std::int32_t& BackInteger();

		/// <summary>
		/// Gets the back const value in Datum
		/// </summary>
		/// <exception cref="runtime_error">Datum type is not Integer</exception>
		/// <returns>A const reference to the integer</returns>
		std::int32_t BackInteger() const;

		/// <summary>
		/// Gets the back value in Datum
		/// </summary>
		/// <exception cref="runtime_error">Datum type is not Float</exception>
		/// <returns>A reference to the float</returns>
		float& BackFloat();

		/// <summary>
		/// Gets the back value in Datum
		/// </summary>
		/// <exception cref="runtime_error">Datum type is not Float</exception>
		/// <returns>A const reference to the float</returns>
		float BackFloat() const;

		/// <summary>
		/// Gets the back value in Datum
		/// </summary>
		/// <exception cref="runtime_error">Datum type is not Vector</exception>
		/// <returns>A reference to the vec4</returns>
		glm::vec4& BackVector();

		/// <summary>
		/// Gets the Back const value in Datum
		/// </summary>
		/// <exception cref="runtime_error">Datum type is not Vector</exception>
		/// <returns>A const reference to the vec4</returns>
		const glm::vec4& BackVector() const;

		/// <summary>
		/// Gets the back value in Datum
		/// </summary>
		/// <exception cref="runtime_error">Datum type is not Matrix</exception>
		/// <returns>A reference to the mat4</returns>
		glm::mat4& BackMatrix();

		/// <summary>
		/// Gets the back const value in Datum
		/// </summary>
		/// <exception cref="runtime_error">Datum type is not Matrix</exception>
		/// <returns>A const reference to the mat4</returns>
		const glm::mat4& BackMatrix() const;

		/// <summary>
		/// Gets the back value in Datum
		/// </summary>
		/// <exception cref="runtime_error">Datum type is not String</exception>
		/// <returns>A reference to the string</returns>
		std::string& BackString();

		/// <summary>
		/// Gets the back const value in Datum
		/// </summary>
		/// <exception cref="runtime_error">Datum type is not String</exception>
		/// <returns>A const reference to the string</returns>
		const std::string& BackString() const;

		/// <summary>
		/// Gets the back value in Datum
		/// </summary>
		/// <exception cref="runtime_error">Datum type is not Pointer</exception>
		/// <returns>A pointer to the RTTI</returns>
		RTTI*& BackPointer();

		/// <summary>
		/// Gets the back const value in Datum
		/// </summary>
		/// <exception cref="runtime_error">Datum type is not Pointer</exception>
		/// <returns>A const pointer to the RTTI</returns>
		const RTTI* BackPointer() const;

		/// <summary>
		/// Remove the first instance of this value in Datum
		/// </summary>
		/// <exception cref="runtime_error">Needs a Integer type Datum to remove an integer</exception>
		/// <param name="value">Value to be removed</param>
		/// <returns></returns>
		bool Remove(std::int32_t value);

		/// <summary>
		/// Remove the first instance of this value in Datum
		/// </summary>
		/// <exception cref="runtime_error">Needs a Float type Datum to remove a float</exception>
		/// <param name="value">Value to be removed</param>
		/// <returns></returns>
		bool Remove(float value);

		/// <summary>
		/// Remove the first instance of this value in Datum
		/// </summary>
		/// <exception cref="runtime_error">Needs a Vector type Datum to remove a vec4</exception>
		/// <param name="value">Value to be removed</param>
		/// <returns></returns>
		bool Remove(const glm::vec4& value);

		/// <summary>
		/// Remove the first instance of this value in Datum
		/// </summary>
		/// <exception cref="runtime_error">Needs a Matrix type Datum to remove a mat4</exception>
		/// <param name="value">Value to be removed</param>
		/// <returns></returns>
		bool Remove(const glm::mat4& value);

		/// <summary>
		/// Remove the first instance of this value in Datum
		/// </summary>
		/// <exception cref="runtime_error">Needs a String type Datum to remove a string</exception>
		/// <param name="value">Value to be removed</param>
		/// <returns></returns>
		bool Remove(const std::string& value);

		/// <summary>
		/// Remove the first instance of this value in Datum
		/// </summary>
		/// <exception cref="runtime_error">Needs a Pointer type Datum to remove a RTTI pointer</exception>
		/// <param name="value">Value to be removed</param>
		/// <returns></returns>
		bool Remove(const RTTI& value);

		/// <summary>
		/// Removes an element at a certain index
		/// </summary>
		/// <exception cref="runtime_error">Cannot remove from a datum with an Unknown type</exception>
		/// <param name="index">index that the value is going to be removed</param>
		/// <returns>bool representing if remove was successful</returns>
		bool RemoveAt(std::size_t index);

		/// <summary>
		/// Finds the first instance of this value in Datum
		/// </summary>
		/// <exception cref="runtime_error">Needs a Integer type Datum to find an integer</exception>
		/// <param name="value">Value to be found</param>
		/// <returns>pair with index of value and bool with whether it was found</returns>
		std::pair<std::size_t, bool> Find(std::int32_t value) const;

		/// <summary>
		/// Finds the first instance of this value in Datum
		/// </summary>
		/// <exception cref="runtime_error">Needs a Float type Datum to find a float</exception>
		/// <param name="value">Value to be found</param>
		/// <returns>pair with index of value and bool with whether it was found</returns>
		std::pair<std::size_t, bool> Find(float value) const;

		/// <summary>
		/// Finds the first instance of this value in Datum
		/// </summary>
		/// <exception cref="runtime_error">Needs a Vector type Datum to find a vec4</exception>
		/// <param name="value">Value to be found</param>
		/// <returns>pair with index of value and bool with whether it was found</returns>
		std::pair<std::size_t, bool> Find(const glm::vec4& value) const;

		/// <summary>
		/// Finds the first instance of this value in Datum
		/// </summary>
		/// <exception cref="runtime_error">Needs a Matrix type Datum to find a mat4</exception>
		/// <param name="value">Value to be found</param>
		/// <returns>pair with index of value and bool with whether it was found</returns>
		std::pair<std::size_t, bool> Find(const glm::mat4& value) const ;

		/// <summary>
		/// Finds the first instance of this value in Datum
		/// </summary>
		/// <exception cref="runtime_error">Needs a String type Datum to find a string</exception>
		/// <param name="value">Value to be found</param>
		/// <returns>pair with index of value and bool with whether it was found</returns>
		std::pair<std::size_t, bool> Find(const std::string& value) const;

		/// <summary>
		/// Finds the first instance of this value in Datum
		/// </summary>
		/// <exception cref="runtime_error">Needs a Pointer type Datum to find a RTTI pointer</exception>
		/// <param name="value">Value to be found</param>
		/// <returns>pair with index of value and bool with whether it was found</returns>
		std::pair<std::size_t, bool> Find(const RTTI& value) const;

		/// <summary>
		/// Turn an index of datum into a string
		/// </summary>
		/// <exception cref="runtime_error">Cannot call ToString on Datum with Unknown or Pointer type</exception>
		/// <param name="index">index to be returned as string</param>
		/// <returns>A string representation of the datum index</returns>
		std::string ToString(std::size_t index = 0) const;

		/// <summary>
		/// Sets a value from a string
		/// </summary>
		/// <exception cref="Not a valid type to use FromString operations on"></exception>
		/// <param name="value">string to be parsed to set value</param>
		/// <param name="index">index to set value</param>
		void SetFromString(const std::string& value, std::size_t index = 0);

		/// <summary>
		/// PushBack a value from a string
		/// </summary>
		/// <exception cref="Not a valid type to use FromString operations on"></exception>
		/// <param name="value">string to be parsed to be pushed back</param>
		void PushBackFromString(const std::string& value);

		/// <summary>
		/// Clears all of the elements out of datum
		/// </summary>
		void Clear();

		/// <summary>
		/// Sets storage type to be external where the Datum does not manage the memory of the data
		/// </summary>
		/// <exception cref="Cannot change datum with internal storage to become an extneral storage Datum"></exception>
		/// <param name="data">pointer to the data</param>
		/// <param name="size">the size of the data</param>
		void SetStorage(std::int32_t* data, std::size_t size);

		/// <summary>
		/// Sets storage type to be external where the Datum does not manage the memory of the data
		/// </summary>
		/// <exception cref="Cannot change datum with internal storage to become an extneral storage Datum"></exception>
		/// <param name="data">pointer to the data</param>
		/// <param name="size">the size of the data</param>
		void SetStorage(float* data, std::size_t size);

		/// <summary>
		/// Sets storage type to be external where the Datum does not manage the memory of the data
		/// </summary>
		/// <exception cref="Cannot change datum with internal storage to become an extneral storage Datum"></exception>
		/// <param name="data">pointer to the data</param>
		/// <param name="size">the size of the data</param>
		void SetStorage(glm::vec4* data, std::size_t size);

		/// <summary>
		/// Sets storage type to be external where the Datum does not manage the memory of the data
		/// </summary>
		/// <exception cref="Cannot change datum with internal storage to become an extneral storage Datum"></exception>
		/// <param name="data">pointer to the data</param>
		/// <param name="size">the size of the data</param>
		void SetStorage(glm::mat4* data, std::size_t size);

		/// <summary>
		/// Sets storage type to be external where the Datum does not manage the memory of the data
		/// </summary>
		/// <exception cref="Cannot change datum with internal storage to become an extneral storage Datum"></exception>
		/// <param name="data">pointer to the data</param>
		/// <param name="size">the size of the data</param>
		void SetStorage(std::string* data, std::size_t size);

		/// <summary>
		/// Sets storage type to be external where the Datum does not manage the memory of the data
		/// </summary>
		/// <exception cref="Cannot change datum with internal storage to become an extneral storage Datum"></exception>
		/// <param name="data">pointer to the data</param>
		/// <param name="size">the size of the data</param>
		void SetStorage(RTTI** data, std::size_t size);

		/// <summary>
		/// Sets storage type to be external where the Datum does not manage the memory of the data
		/// </summary>
		/// <exception cref="Cannot change datum with internal storage to become an extneral storage Datum"></exception>
		/// <param name="data">pointer to the data</param>
		/// <param name="size">the size of the data</param>
		void SetStorage(Scope** data, std::size_t size);

		/// <summary>
		/// Returns whether Datum has external storage
		/// </summary>
		/// <returns>bool representing if it has external storage</returns>
		bool IsExternalStorage() const;

		/// <summary>
		/// Operator for Scope type datums
		/// </summary>
		/// <param name="index">index to get the scope at</param>
		/// <returns>The scope at index</returns>
		Scope& operator[](std::size_t index);

	private:
		/// <summary>
		/// RTTI Pointer Typecast constructor
		/// </summary>
		/// <param name="other">Value being assigned</param>
		Datum(Scope& value);
		
		/// <summary>
		/// Adds a Scope pointer to the back of the Datum
		/// </summary>
		/// <exception cref="runtime_error">Must be type Table to insert a Scope pointer</exception>
		/// <param name="value">RTTI pointer being added</param>
		void PushBack(Scope& value);

		/// <summary>
		/// RTTI Pointer Assignment Operator
		/// </summary>
		/// <exception cref="runtime_error">Cannot use assignment operator on Datum that has a known type</exception>
		/// <param name="other">Value being assigned</param>
		/// <returns>Datum being copied to</returns>
		Datum& operator=(Scope& value);

		/// <summary>
		/// Sets a value in Datum
		/// </summary>
		/// <exception cref="runtime_error">Datum type is not Pointer</exception>
		/// <exception cref="out_of_range">Index is not a valid index in Datum</exception>
		/// <param name="value">Value to set index to</param>
		/// <param name="index">index to be set</param>
		void Set(Scope& value, std::size_t index = 0);

		void SetStorage(void* data, std::size_t size);

		union DatumValues final
		{
			std::int32_t* i;
			float* f;
			glm::vec4* v;
			glm::mat4* m;
			std::string* s;
			RTTI** r;
			Scope** t;
			void* vp;
			std::int8_t* b= { nullptr };
		};

		DatumValues _data;
		std::size_t _capacity{ 0 };
		std::size_t _size{ 0 };
		DatumTypes _type{ DatumTypes::Unknown };
		bool _isExternalStorage{ false };
		static const std::size_t DatumTypeSizes[static_cast<std::size_t>(DatumTypes::Pointer) + 1];
	};
}

#include "Datum.inl"