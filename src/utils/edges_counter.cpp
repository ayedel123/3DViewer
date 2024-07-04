#include "edges_counter.h"

QSet<int> getEdgeSet(int start, int end) {
  QSet<int> rib;

  rib.insert(start);
  rib.insert(end);

  return reinterpret_cast<const QSet<int> &>(rib);
}

int countEdges(Model model) {
  auto edges = new QSet<QSet<int>>();

  for (int i = 0; i < model.facesCount; i++) {
    auto face = model.faces[i];

    if (face.vertexesCount > 1) {
      edges->insert(
          getEdgeSet(face.vertexes[0], face.vertexes[face.vertexesCount - 1]));
    }

    if (face.vertexesCount == 2) break;

    for (int j = 0; j < face.vertexesCount - 1; j++) {
      edges->insert(getEdgeSet(face.vertexes[j], face.vertexes[j + 1]));
    }
  }

  return (int)edges->count();
}
