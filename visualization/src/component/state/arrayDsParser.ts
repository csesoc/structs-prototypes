import { ArrayNode, ArrayDataStructure, SupportDataType, State, VariableType } from './state'; // Replace with the actual file name containing your types

function generateRandomArrayData(
  minValue: number,
  maxValue: number,
  length: number,
): ArrayDataStructure {
  const getRandomValue = (min: number, max: number): number =>
    Math.floor(Math.random() * (max - min + 1)) + min;
  const getAddress = (index: number): string =>
    `0x${(1000000 + index * 4).toString(16)}`;

  const data: ArrayNode[] = [];

  for (let i = 0; i < length; i++) {
    data.push({
      addr: getAddress(i),
      data: getRandomValue(minValue, maxValue).toString(),
    });
  }

  return {
    type: SupportDataType.ARRAY,
    data,
  };
}

function generateIncrementingArrayData(
  minValue: number,
  maxValue: number,
  length: number,
): ArrayDataStructure {
  const incrementValue = (maxValue - minValue) / (length - 1);
  const getAddress = (index: number): string =>
    `0x${(1000000 + index * 4).toString(16)}`;

  const data: ArrayNode[] = [];

  for (let i = 0; i < length; i++) {
    data.push({
      addr: getAddress(i),
      data: Math.round(minValue + i * incrementValue).toString(),
    });
  }

  return {
    type: SupportDataType.ARRAY,
    data,
  };
}

/**
 * Randomly generate an array data structure
 */
export function parseArrayState(isOrder: boolean): ArrayDataStructure {
  if (isOrder) {
    return generateIncrementingArrayData(0, 100, 10);
  } else {
    return generateRandomArrayData(0, 100, 10);
  }
}

export function generateArrayState(): State {
  let ds = parseArrayState(false);
  return {
    variables: [
      {
        type: VariableType.POINTER,
        name: 'curr',
        addr: ds.data[0].addr,
        value: ds.data[0].data.toString(),
      },
    ],
    dataStructure: ds,
  };
}

export function generateIncreArrayState(): State {
  let ds = parseArrayState(true);
  return {
    variables: [
      {
        type: VariableType.POINTER,
        name: 'curr',
        addr: ds.data[0].addr,
        value: ds.data[0].data.toString(),
      },
      {
        type: VariableType.INT,
        name: 'sum',
        value: ds.data[0].data.toString(),
      },
    ],
    dataStructure: ds,
  };
}