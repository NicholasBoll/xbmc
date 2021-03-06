/*
 *      Copyright (C) 2005-2012 Team XBMC
 *      http://www.xbmc.org
 *
 *  This Program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *
 *  This Program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with XBMC; see the file COPYING.  If not, see
 *  <http://www.gnu.org/licenses/>.
 *
 */

#include "utils/StringUtils.h"

#include "gtest/gtest.h"

TEST(TestStringUtils, JoinString)
{
  CStdString refstr, varstr;
  CStdStringArray strarray;

  strarray.push_back("a");
  strarray.push_back("b");
  strarray.push_back("c");
  strarray.push_back("de");
  strarray.push_back(",");
  strarray.push_back("fg");
  strarray.push_back(",");
  refstr = "a,b,c,de,,,fg,,";
  StringUtils::JoinString(strarray, ",", varstr);
  EXPECT_STREQ(refstr.c_str(), varstr.c_str());

  strarray.clear();
  varstr.clear();
  strarray.push_back("g");
  strarray.push_back("h");
  strarray.push_back("i");
  strarray.push_back("jk,");
  strarray.push_back(",");
  strarray.push_back("lmn,,");
  strarray.push_back(",");
  refstr = "g,h,i,jk,,,,lmn,,,,";
  varstr = StringUtils::JoinString(strarray, ",");
  EXPECT_STREQ(refstr.c_str(), varstr.c_str());
}

TEST(TestStringUtils, Join)
{
  CStdString refstr, varstr;
  std::vector<std::string> strarray;

  strarray.push_back("a");
  strarray.push_back("b");
  strarray.push_back("c");
  strarray.push_back("de");
  strarray.push_back(",");
  strarray.push_back("fg");
  strarray.push_back(",");
  refstr = "a,b,c,de,,,fg,,";
  varstr = StringUtils::Join(strarray, ",");
  EXPECT_STREQ(refstr.c_str(), varstr.c_str());
}

TEST(TestStringUtils, SplitString)
{
  CStdStringArray varresults;

  EXPECT_EQ(9, StringUtils::SplitString("a,b,c,de,,,fg,,", ",", varresults));
  EXPECT_STREQ("a", varresults.at(0).c_str());
  EXPECT_STREQ("b", varresults.at(1).c_str());
  EXPECT_STREQ("c", varresults.at(2).c_str());
  EXPECT_STREQ("de", varresults.at(3).c_str());
  EXPECT_STREQ("", varresults.at(4).c_str());
  EXPECT_STREQ("", varresults.at(5).c_str());
  EXPECT_STREQ("fg", varresults.at(6).c_str());
  EXPECT_STREQ("", varresults.at(7).c_str());
  EXPECT_STREQ("", varresults.at(8).c_str());

  varresults.clear();
  varresults = StringUtils::SplitString("g,h,ij,k,lm,,n", ",");
  EXPECT_STREQ("g", varresults.at(0).c_str());
  EXPECT_STREQ("h", varresults.at(1).c_str());
  EXPECT_STREQ("ij", varresults.at(2).c_str());
  EXPECT_STREQ("k", varresults.at(3).c_str());
  EXPECT_STREQ("lm", varresults.at(4).c_str());
  EXPECT_STREQ("", varresults.at(5).c_str());
  EXPECT_STREQ("n", varresults.at(6).c_str());
}

TEST(TestStringUtils, Split)
{
  std::vector<std::string> varresults;

  varresults = StringUtils::Split("g,h,ij,k,lm,,n", ",");
  EXPECT_STREQ("g", varresults.at(0).c_str());
  EXPECT_STREQ("h", varresults.at(1).c_str());
  EXPECT_STREQ("ij", varresults.at(2).c_str());
  EXPECT_STREQ("k", varresults.at(3).c_str());
  EXPECT_STREQ("lm", varresults.at(4).c_str());
  EXPECT_STREQ("", varresults.at(5).c_str());
  EXPECT_STREQ("n", varresults.at(6).c_str());
}

TEST(TestStringUtils, FindNumber)
{
  EXPECT_EQ(3, StringUtils::FindNumber("aabcaadeaa", "aa"));
  EXPECT_EQ(1, StringUtils::FindNumber("aabcaadeaa", "b"));
}

TEST(TestStringUtils, AlphaNumericCompare)
{
  int64_t ref, var;

  ref = 0;
  var = StringUtils::AlphaNumericCompare(L"123abc", L"abc123");
  EXPECT_LT(var, ref);
}

TEST(TestStringUtils, TimeStringToSeconds)
{
  long ref, var;

  ref = 77455;
  var = StringUtils::TimeStringToSeconds("21:30:55");
  EXPECT_EQ(ref, var);
}

TEST(TestStringUtils, RemoveCRLF)
{
  CStdString refstr, varstr;

  refstr = "test\r\nstring\nblah blah";
  varstr = "test\r\nstring\nblah blah\n";
  StringUtils::RemoveCRLF(varstr);
  EXPECT_STREQ(refstr.c_str(), varstr.c_str());
}

TEST(TestStringUtils, utf8_strlen)
{
  int ref, var;

  ref = 9;
  var = StringUtils::utf8_strlen("ｔｅｓｔ＿ＵＴＦ８");
  EXPECT_EQ(ref, var);
}

TEST(TestStringUtils, SecondsToTimeString)
{
  CStdString ref, var;

  ref = "21:30:55";
  var = StringUtils::SecondsToTimeString(77455);
  EXPECT_STREQ(ref.c_str(), var.c_str());
}

TEST(TestStringUtils, IsNaturalNumber)
{
  EXPECT_TRUE(StringUtils::IsNaturalNumber("10"));
  EXPECT_TRUE(StringUtils::IsNaturalNumber(" 10"));
  EXPECT_TRUE(StringUtils::IsNaturalNumber("0"));
  EXPECT_FALSE(StringUtils::IsNaturalNumber(" 1 0"));
  EXPECT_FALSE(StringUtils::IsNaturalNumber("1.0"));
  EXPECT_FALSE(StringUtils::IsNaturalNumber("1.1"));
  EXPECT_FALSE(StringUtils::IsNaturalNumber("0x1"));
  EXPECT_FALSE(StringUtils::IsNaturalNumber("blah"));
  EXPECT_FALSE(StringUtils::IsNaturalNumber("120 h"));
  EXPECT_FALSE(StringUtils::IsNaturalNumber(" "));
  EXPECT_FALSE(StringUtils::IsNaturalNumber(""));
}

TEST(TestStringUtils, IsInteger)
{
  EXPECT_TRUE(StringUtils::IsInteger("10"));
  EXPECT_TRUE(StringUtils::IsInteger(" -10"));
  EXPECT_TRUE(StringUtils::IsInteger("0"));
  EXPECT_FALSE(StringUtils::IsInteger(" 1 0"));
  EXPECT_FALSE(StringUtils::IsInteger("1.0"));
  EXPECT_FALSE(StringUtils::IsInteger("1.1"));
  EXPECT_FALSE(StringUtils::IsInteger("0x1"));
  EXPECT_FALSE(StringUtils::IsInteger("blah"));
  EXPECT_FALSE(StringUtils::IsInteger("120 h"));
  EXPECT_FALSE(StringUtils::IsInteger(" "));
  EXPECT_FALSE(StringUtils::IsInteger(""));
}

TEST(TestStringUtils, SizeToString)
{
  CStdString ref, var;

  ref = "2.00 GB";
  var = StringUtils::SizeToString(2147483647);
  EXPECT_STREQ(ref.c_str(), var.c_str());
}

TEST(TestStringUtils, EmptyString)
{
  EXPECT_STREQ("", StringUtils::EmptyString.c_str());
}

TEST(TestStringUtils, FindWords)
{
  int ref, var;

  ref = 5;
  var = StringUtils::FindWords("test string", "string");
  EXPECT_EQ(ref, var);
}

TEST(TestStringUtils, FindEndBracket)
{
  int ref, var;

  ref = 11;
  var = StringUtils::FindEndBracket("atest testbb test", 'a', 'b');
  EXPECT_EQ(ref, var);
}

TEST(TestStringUtils, DateStringToYYYYMMDD)
{
  int ref, var;

  ref = 20120706;
  var = StringUtils::DateStringToYYYYMMDD("2012-07-06");
  EXPECT_EQ(ref, var);
}

TEST(TestStringUtils, WordToDigits)
{
  CStdString ref, var;

  ref = "8378 787464";
  var = "test string";
  StringUtils::WordToDigits(var);
  EXPECT_STREQ(ref.c_str(), var.c_str());
}

TEST(TestStringUtils, CreateUUID)
{
  std::cout << "CreateUUID(): " << StringUtils::CreateUUID() << "\n";
}

TEST(TestStringUtils, ValidateUUID)
{
  EXPECT_TRUE(StringUtils::ValidateUUID(StringUtils::CreateUUID()));
}

TEST(TestStringUtils, CompareFuzzy)
{
  double ref, var;

  ref = 6.25f;
  var = StringUtils::CompareFuzzy("test string", "string test");
  EXPECT_EQ(ref, var);
}

TEST(TestStringUtils, FindBestMatch)
{
  double refdouble, vardouble;
  int refint, varint;
  CStdStringArray strarray;

  refint = 3;
  refdouble = 0.5625f;
  strarray.push_back("");
  strarray.push_back("a");
  strarray.push_back("e");
  strarray.push_back("es");
  strarray.push_back("t");
  varint = StringUtils::FindBestMatch("test", strarray, vardouble);
  EXPECT_EQ(refint, varint);
  EXPECT_EQ(refdouble, vardouble);
}
