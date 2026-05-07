import pandas as pd
import numpy as np

# --- Initialization ---
# Read the iris.csv file into a Pandas DataFrame
print("Reading the dataset...")
df = pd.read_csv('iris.csv')

# --- a. Identify and count missing values ---
missing_counts = df.isnull().sum()
print("\n--- Missing Values per Column ---")
print(missing_counts)

# --- b. Drop the column having more than 5 null values ---
# Find columns where the count of nulls is greater than 5
cols_to_drop = missing_counts[missing_counts > 5].index
df = df.drop(columns=cols_to_drop)
print(f"\nDropped columns with > 5 nulls: {list(cols_to_drop)}")

# --- c. Identify row label with max sum of all values and drop it ---
# We use numeric_only=True so we don't accidentally try to sum string columns (like 'species')
row_sums = df.sum(axis=1, numeric_only=True)
max_sum_row_label = row_sums.idxmax() # idxmax() gets the index label of the maximum value
df = df.drop(index=max_sum_row_label)
print(f"\nDropped row with maximum sum. Row label: {max_sum_row_label}")

# --- d. Sort the dataframe on the basis of the first column ---
# df.columns[0] gets the name of the very first column dynamically
first_column = df.columns[0]
df = df.sort_values(by=first_column)
print(f"\nSorted DataFrame based on column: '{first_column}'")

# --- e. Remove all duplicates from the first column ---
# Keep only the first occurrence of each value in the first column
df = df.drop_duplicates(subset=[first_column])
print(f"\nRemoved duplicates from column: '{first_column}'")

# --- f. Find correlation (1st & 2nd col) and covariance (2nd & 3rd col) ---
second_column = df.columns[1]
third_column = df.columns[2]

# Correlation between Col 1 and Col 2
correlation = df[first_column].corr(df[second_column])
# Covariance between Col 2 and Col 3
covariance = df[second_column].cov(df[third_column])

print(f"\nCorrelation between '{first_column}' and '{second_column}': {correlation:.4f}")
print(f"Covariance between '{second_column}' and '{third_column}': {covariance:.4f}")

# --- g. Detect outliers and remove rows having outliers ---
# Standard ML practice: Use IQR (Interquartile Range) for outlier detection
# Step 1: Select only numeric columns
numeric_cols = df.select_dtypes(include=[np.number]).columns

# Step 2: Calculate Q1, Q3, and IQR
Q1 = df[numeric_cols].quantile(0.25)
Q3 = df[numeric_cols].quantile(0.75)
IQR = Q3 - Q1

# Step 3: Define the condition for rows to KEEP (values within 1.5 * IQR)
# A ~ (tilde) means "NOT". We are keeping rows that do NOT have outliers.
condition = ~((df[numeric_cols] < (Q1 - 1.5 * IQR)) | (df[numeric_cols] > (Q3 + 1.5 * IQR))).any(axis=1)
df = df[condition]
print("\nRemoved rows containing outliers.")

# --- h. Discretize second column and create 5 bins ---
# pd.cut automatically divides the data into equally spaced bins
# We will create a new column to store these bins so we don't lose the original data
df['discretized_bins'] = pd.cut(df[second_column], bins=5)
print(f"\nDiscretized '{second_column}' into 5 bins:")
print(df['discretized_bins'].value_counts())

# --- Final Step: Save the cleaned data ---
# It's always good practice to save your transformed data to a new file!
df.to_csv('cleaned_iris.csv', index=False)
print("\nSuccess! Cleaned dataset saved as 'cleaned_iris.csv'.")