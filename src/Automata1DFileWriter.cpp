// #include "AutomataControllers.hpp"

// Automata1DFileWriter::Automata1DFileWriter(Automata1DModel* ptr, const std::string& filename):
//     writeStream {filename}
//     {
//         model_ptr.reset(ptr);
//     }

// void Automata1DFileWriter::writeBoard() const {
//     const Board1DType& board {model_ptr->getBoard()}; 
//     for (auto iter = begin(board); iter != end(board); ++iter) {
//         writeStream << *iter << ' ';
//     }
//     writeStream << '\n';
// }