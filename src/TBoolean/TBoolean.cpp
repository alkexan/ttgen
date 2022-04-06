#include "TBoolean.hpp"

using namespace thl;

TBoolean::TBoolean() : m_value(UNKNOWN) {}

TBoolean::~TBoolean() {}

signed char TBoolean::getValue() const { return m_value; }

TBoolean::operator std::string() {
  std::string result;
  switch (m_value) {
  case FALSE:
    result = "FALSE";
    break;
  case UNKNOWN:
    result = "UNKNOWN";
    break;
  case TRUE:
    result = "TRUE";
    break;
  }
  return result;
}

TBoolean &TBoolean::operator=(TBoolean y) {
  m_value = y.getValue();
  return *this;
}

TBoolean TBoolean::operator-() { return TBoolean(-m_value); }

TBoolean TBoolean::operator+() { return TBoolean(+m_value); }

TBoolean TBoolean::operator~() {
  signed char result = m_value;
  switch (result) {
  case FALSE:
    result = TRUE;
    break;
  case UNKNOWN:
    result = UNKNOWN;
    break;
  case TRUE:
    result = FALSE;
    break;
  }
  return TBoolean(result);
}

TBoolean &TBoolean::operator--() {
  switch (m_value) {
  case FALSE:
    m_value = TRUE;
    break;
  case UNKNOWN:
    m_value = FALSE;
    break;
  case TRUE:
    m_value = UNKNOWN;
    break;
  }
  return *this;
}

TBoolean TBoolean::operator--(int) {
  TBoolean prev = *this;
  --(*this);
  return prev;
}

TBoolean &TBoolean::operator++() {
  switch (m_value) {
  case FALSE:
    m_value = UNKNOWN;
    break;
  case UNKNOWN:
    m_value = TRUE;
    break;
  case TRUE:
    m_value = FALSE;
    break;
  }
  return *this;
}

TBoolean TBoolean::operator++(int) {
  TBoolean prev = *this;
  ++(*this);
  return prev;
}

TBoolean TBoolean::operator|(TBoolean y) {
  TBoolean result = UNKNOWN;
  switch (m_value) {
  case FALSE: {
    switch (y.getValue()) {
    case FALSE:
      result = FALSE;
      break;
    case UNKNOWN:
      result = UNKNOWN;
      break;
    case TRUE:
      result = TRUE;
      break;
    }
    break;
  }
  case UNKNOWN: {
    switch (y.getValue()) {
    case FALSE:
      result = UNKNOWN;
      break;
    case UNKNOWN:
      result = UNKNOWN;
      break;
    case TRUE:
      result = TRUE;
      break;
    }
    break;
  }
  case TRUE: {
    switch (y.getValue()) {
    case FALSE:
      result = TRUE;
      break;
    case UNKNOWN:
      result = TRUE;
      break;
    case TRUE:
      result = TRUE;
      break;
    }
    break;
  }
  }
  return result;
}

TBoolean TBoolean::operator&(TBoolean y) {
  TBoolean result = UNKNOWN;
  switch (m_value) {
  case FALSE: {
    switch (y.getValue()) {
    case FALSE:
      result = FALSE;
      break;
    case UNKNOWN:
      result = FALSE;
      break;
    case TRUE:
      result = FALSE;
      break;
    }
    break;
  }
  case UNKNOWN: {
    switch (y.getValue()) {
    case FALSE:
      result = FALSE;
      break;
    case UNKNOWN:
      result = UNKNOWN;
      break;
    case TRUE:
      result = UNKNOWN;
      break;
    }
    break;
  }
  case TRUE: {
    switch (y.getValue()) {
    case FALSE:
      result = FALSE;
      break;
    case UNKNOWN:
      result = UNKNOWN;
      break;
    case TRUE:
      result = TRUE;
      break;
    }
    break;
  }
  }
  return result;
}

TBoolean TBoolean::operator/(TBoolean y) {
  TBoolean result = UNKNOWN;
  switch (m_value) {
  case FALSE: {
    switch (y.getValue()) {
    case FALSE:
      result = FALSE;
      break;
    case UNKNOWN:
      result = UNKNOWN;
      break;
    case TRUE:
      result = FALSE;
      break;
    }
    break;
  }
  case UNKNOWN: {
    switch (y.getValue()) {
    case FALSE:
      result = UNKNOWN;
      break;
    case UNKNOWN:
      result = UNKNOWN;
      break;
    case TRUE:
      result = FALSE;
      break;
    }
    break;
  }
  case TRUE: {
    switch (y.getValue()) {
    case FALSE:
      result = TRUE;
      break;
    case UNKNOWN:
      result = UNKNOWN;
      break;
    case TRUE:
      result = FALSE;
      break;
    }
    break;
  }
  }
  return result;
}

TBoolean TBoolean::operator^(TBoolean y) {
  TBoolean result = UNKNOWN;
  switch (m_value) {
  case FALSE: {
    switch (y.getValue()) {
    case FALSE:
      result = FALSE;
      break;
    case UNKNOWN:
      result = UNKNOWN;
      break;
    case TRUE:
      result = TRUE;
      break;
    }
    break;
  }
  case UNKNOWN: {
    switch (y.getValue()) {
    case FALSE:
      result = UNKNOWN;
      break;
    case UNKNOWN:
      result = UNKNOWN;
      break;
    case TRUE:
      result = UNKNOWN;
      break;
    }
    break;
  }
  case TRUE: {
    switch (y.getValue()) {
    case FALSE:
      result = TRUE;
      break;
    case UNKNOWN:
      result = UNKNOWN;
      break;
    case TRUE:
      result = FALSE;
      break;
    }
    break;
  }
  }
  return result;
}

TBoolean TBoolean::operator%(TBoolean y) {
  TBoolean result = UNKNOWN;
  switch (m_value) {
  case FALSE: {
    switch (y.getValue()) {
    case FALSE:
      result = TRUE;
      break;
    case UNKNOWN:
      result = FALSE;
      break;
    case TRUE:
      result = UNKNOWN;
      break;
    }
    break;
  }
  case UNKNOWN: {
    switch (y.getValue()) {
    case FALSE:
      result = FALSE;
      break;
    case UNKNOWN:
      result = UNKNOWN;
      break;
    case TRUE:
      result = TRUE;
      break;
    }
    break;
  }
  case TRUE: {
    switch (y.getValue()) {
    case FALSE:
      result = UNKNOWN;
      break;
    case UNKNOWN:
      result = TRUE;
      break;
    case TRUE:
      result = FALSE;
      break;
    }
    break;
  }
  }
  return result;
}

TBoolean TBoolean::operator+(TBoolean y) {
  TBoolean result = UNKNOWN;
  switch (m_value) {
  case FALSE: {
    switch (y.getValue()) {
    case FALSE:
      result = FALSE;
      break;
    case UNKNOWN:
      result = FALSE;
      break;
    case TRUE:
      result = UNKNOWN;
      break;
    }
    break;
  }
  case UNKNOWN: {
    switch (y.getValue()) {
    case FALSE:
      result = FALSE;
      break;
    case UNKNOWN:
      result = UNKNOWN;
      break;
    case TRUE:
      result = TRUE;
      break;
    }
    break;
  }
  case TRUE: {
    switch (y.getValue()) {
    case FALSE:
      result = UNKNOWN;
      break;
    case UNKNOWN:
      result = TRUE;
      break;
    case TRUE:
      result = TRUE;
      break;
    }
    break;
  }
  }
  return result;
}

TBoolean TBoolean::operator*(TBoolean y) {
  TBoolean result = UNKNOWN;
  switch (m_value) {
  case FALSE: {
    switch (y.getValue()) {
    case FALSE:
      result = TRUE;
      break;
    case UNKNOWN:
      result = UNKNOWN;
      break;
    case TRUE:
      result = FALSE;
      break;
    }
    break;
  }
  case UNKNOWN: {
    switch (y.getValue()) {
    case FALSE:
      result = UNKNOWN;
      break;
    case UNKNOWN:
      result = UNKNOWN;
      break;
    case TRUE:
      result = UNKNOWN;
      break;
    }
    break;
  }
  case TRUE: {
    switch (y.getValue()) {
    case FALSE:
      result = FALSE;
      break;
    case UNKNOWN:
      result = UNKNOWN;
      break;
    case TRUE:
      result = TRUE;
      break;
    }
    break;
  }
  }
  return result;
}

TBoolean TBoolean::operator-(TBoolean y) {
  TBoolean result = UNKNOWN;
  switch (m_value) {
  case FALSE: {
    switch (y.getValue()) {
    case FALSE:
      result = UNKNOWN;
      break;
    case UNKNOWN:
      result = FALSE;
      break;
    case TRUE:
      result = FALSE;
      break;
    }
    break;
  }
  case UNKNOWN: {
    switch (y.getValue()) {
    case FALSE:
      result = TRUE;
      break;
    case UNKNOWN:
      result = UNKNOWN;
      break;
    case TRUE:
      result = FALSE;
      break;
    }
    break;
  }
  case TRUE: {
    switch (y.getValue()) {
    case FALSE:
      result = TRUE;
      break;
    case UNKNOWN:
      result = TRUE;
      break;
    case TRUE:
      result = UNKNOWN;
      break;
    }
    break;
  }
  }
  return result;
}

TBoolean TBoolean::comp(TBoolean y) { return ~((*this) - y); }

TBoolean TBoolean::nand(TBoolean y) { return ~((*this) & y); }

TBoolean TBoolean::nor(TBoolean y) { return ~((*this) | y); }

TBoolean TBoolean::impl(TBoolean y) {
  TBoolean result = UNKNOWN;
  switch (m_value) {
  case FALSE: {
    switch (y.getValue()) {
    case FALSE:
      result = TRUE;
      break;
    case UNKNOWN:
      result = TRUE;
      break;
    case TRUE:
      result = TRUE;
      break;
    }
    break;
  }
  case UNKNOWN: {
    switch (y.getValue()) {
    case FALSE:
      result = UNKNOWN;
      break;
    case UNKNOWN:
      result = UNKNOWN;
      break;
    case TRUE:
      result = TRUE;
      break;
    }
    break;
  }
  case TRUE: {
    switch (y.getValue()) {
    case FALSE:
      result = FALSE;
      break;
    case UNKNOWN:
      result = UNKNOWN;
      break;
    case TRUE:
      result = TRUE;
      break;
    }
    break;
  }
  }
  return result;
}

TBoolean TBoolean::implb(TBoolean y) {
  TBoolean result = UNKNOWN;
  switch (m_value) {
  case FALSE: {
    switch (y.getValue()) {
    case FALSE:
      result = TRUE;
      break;
    case UNKNOWN:
      result = UNKNOWN;
      break;
    case TRUE:
      result = UNKNOWN;
      break;
    }
    break;
  }
  case UNKNOWN: {
    switch (y.getValue()) {
    case FALSE:
      result = UNKNOWN;
      break;
    case UNKNOWN:
      result = UNKNOWN;
      break;
    case TRUE:
      result = UNKNOWN;
      break;
    }
    break;
  }
  case TRUE: {
    switch (y.getValue()) {
    case FALSE:
      result = FALSE;
      break;
    case UNKNOWN:
      result = UNKNOWN;
      break;
    case TRUE:
      result = TRUE;
      break;
    }
    break;
  }
  }
  return result;
}
