.pragma library
.import QtQuick as QtQuick


// Calculation related
const minFreq = 20
const maxFreq = 20000
const octaveRange = Math.log2(maxFreq) - Math.log2(minFreq)
const ampRange = 36

function getRelativeFreqPosition(freq) {
    return (Math.log2(freq) - Math.log2(minFreq)) / octaveRange
}

function getOctaveFromFreq(freq) {
    return Math.log2(freq/minFreq)
}

function getFreqFromOctave(octave) {
    return 2**octave * minFreq
}

function getFreqFromRelativePosition(position) {
    return 2**(position * octaveRange) * minFreq
}

function getRelateiveAmplitudePosition(db) {
    if (db > 0)
        return 0.5 - db / ampRange
    else if (db == 0)
        return 0.5
    else
        return Math.abs(db) / ampRange + 0.5
}

function calculateCirclePoint(angle, radius, centerPoint) {
    const posX = radius * Math.cos(angle * Math.PI / 180) + centerPoint.x
    const posY = radius * Math.sin(angle * Math.PI / 180) + centerPoint.y

    return Qt.point(posX, posY)
}

function round(value, precision) {
    const multiplier = Math.pow(10, precision || 0)
    return Math.round(value * multiplier) / multiplier
}
